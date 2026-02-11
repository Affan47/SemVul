compile(const ConcreteNodeListPtr &nodes, const String &group)
    {

        mGroup = group;


        mErrors.clear();


        mEnv.clear();

        if(mListener)
            mListener->preConversion(this, nodes);


        AbstractNodeListPtr ast = convertToAST(nodes);

        processImports(ast);

        processObjects(ast.get(), ast);

        processVariables(ast.get());


        if(mListener && !mListener->postConversion(this, ast))
            return mErrors.empty();


        for(AbstractNodeList::iterator i = ast->begin(); i != ast->end(); ++i)
        {

            if((*i)->type == ANT_OBJECT && static_cast<ObjectAbstractNode*>((*i).get())->abstract)
                continue;

            ScriptTranslator *translator = ScriptCompilerManager::getSingleton().getTranslator(*i);
            if(translator)
                translator->translate(this, *i);
        }

        mImports.clear();
        mImportRequests.clear();
        mImportTable.clear();

        return mErrors.empty();
    }
