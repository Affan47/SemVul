applyTextureAliases(const AliasTextureNamePairList& aliasList, const bool apply) const
    {

        Techniques::const_iterator i, iend;
        iend = mTechniques.end();
        bool testResult = false;

        for (i = mTechniques.begin(); i != iend; ++i)
        {
            if ((*i)->applyTextureAliases(aliasList, apply))
                testResult = true;
        }

        return testResult;
    }
