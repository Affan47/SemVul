mergeModules()
{
    for(ContainedList::iterator p = _contents.begin(); p != _contents.end(); ++p)
    {
        ModulePtr mod1 = ModulePtr::dynamicCast(*p);
        if(!mod1)
        {
            continue;
        }

        DefinitionContextPtr dc1 = mod1->definitionContext();
        assert(dc1);
        StringList metaData1 = dc1->getMetaData();
        metaData1.sort();
        metaData1.unique();

        ContainedList::iterator q = p;
        ++q;
        while(q != _contents.end())
        {
            ModulePtr mod2 = ModulePtr::dynamicCast(*q);
            if(!mod2)
            {
                ++q;
                continue;
            }

            if(mod1->name() != mod2->name())
            {
                ++q;
                continue;
            }


            DefinitionContextPtr dc2 = mod2->definitionContext();
            assert(dc2);
            StringList metaData2 = dc2->getMetaData();
            metaData2.sort();
            metaData2.unique();
            if(metaData1 != metaData2)
            {
                unit()->warning("global metadata mismatch for module `" + mod1->name() + "' in files " +
                                dc1->filename() + " and " + dc2->filename());
            }

            mod1->_contents.splice(mod1->_contents.end(), mod2->_contents);

            if(mod1->_comment.length() < mod2->_comment.length())
            {
                mod1->_comment.swap(mod2->_comment);
            }

            mod1->_includeLevel = min(mod1->_includeLevel, mod2->_includeLevel);

            _unit->removeContent(*q);
            q = _contents.erase(q);
        }

        mod1->mergeModules();
    }
}
