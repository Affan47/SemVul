queryInstSources(EvalState & state,
    const InstallSourceInfo & instSource, const Strings & args,
    DrvInfos & elems, bool newestOnly)
{
    InstallSourceType type = instSource.type;
    if (type == srcUnknown && args.size() > 0 && isPath(args.front()))
        type = srcStorePaths;

    switch (type) {


        case srcUnknown:
        case srcNixExprDrvs: {


            DrvInfos allElems;
            loadDerivations(state, instSource.nixExprPath,
                instSource.systemFilter, instSource.autoArgs, "", allElems);

            elems = filterBySelector(state, allElems, args,
                newestOnly, instSource.prebuiltOnly);

            break;
        }


        case srcNixExprs: {

            Expr * e1 = loadSourceExpr(state, instSource.nixExprPath);

            foreach (Strings::const_iterator, i, args) {
                Expr * e2 = parseExprFromString(state, *i, absPath("."));
                Expr * call = new ExprApp(e2, e1);
                Value v; state.eval(call, v);
                getDerivations(state, v, "", instSource.autoArgs, elems);
            }

            break;
        }


        case srcStorePaths: {

            for (Strings::const_iterator i = args.begin();
                 i != args.end(); ++i)
            {
                Path path = followLinksToStorePath(*i);

                DrvInfo elem;
                elem.attrs = new Bindings;
                string name = baseNameOf(path);
                string::size_type dash = name.find('-');
                if (dash != string::npos)
                    name = string(name, dash + 1);

                if (isDerivation(path)) {
                    elem.setDrvPath(path);
                    elem.setOutPath(findOutput(derivationFromPath(path), "out"));
                    if (name.size() >= drvExtension.size() &&
                        string(name, name.size() - drvExtension.size()) == drvExtension)
                        name = string(name, 0, name.size() - drvExtension.size());
                }
                else elem.setOutPath(path);

                elem.name = name;

                elems.push_back(elem);
            }

            break;
        }


        case srcProfile: {
            elems = filterBySelector(state,
                queryInstalled(state, instSource.profile),
                args, newestOnly, instSource.prebuiltOnly);
            break;
        }

        case srcAttrPath: {
            foreach (Strings::const_iterator, i, args) {
                Value v;
                findAlongAttrPath(state, *i, instSource.autoArgs,
                    loadSourceExpr(state, instSource.nixExprPath), v);
                getDerivations(state, v, "", instSource.autoArgs, elems);
            }
            break;
        }
    }
}
