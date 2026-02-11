visitOperation(const OperationPtr& p)
{
    string name = fixKwd(p->name());
    ContainerPtr container = p->container();
    ClassDefPtr cl = ClassDefPtr::dynamicCast(container);
    string package = getPackage(cl);

    Output& out = output();

    TypePtr ret = p->returnType();
    string retS = typeToString(ret, TypeModeReturn, package, p->getMetaData());
    vector<string> params = getParams(p, package);
    ExceptionList throws = p->throws();
    throws.sort();
    throws.unique();

    string deprecateReason = getDeprecateReason(p, cl, "type");


    out << sp;
    if(!deprecateReason.empty())
    {
        out << nl << "/**";
        out << nl << " * @deprecated " << deprecateReason;
        out << nl << " **/";
    }
    out << nl << "public " << retS << ' ' << name << spar << params << epar;
    writeThrowsClause(package, throws);
    out << ';';
    if(!deprecateReason.empty())
    {
        out << nl << "/**";
        out << nl << " * @deprecated " << deprecateReason;
        out << nl << " **/";
    }
    out << nl << "public " << retS << ' ' << name << spar << params << "java.util.Hashtable __ctx" << epar;
    writeThrowsClause(package, throws);
    out << ';';
}
