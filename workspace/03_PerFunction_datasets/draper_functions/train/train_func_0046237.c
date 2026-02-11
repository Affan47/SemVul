prepareImpl(void)
    {

        if (mCompilationRequired)
            compile();


        Techniques::iterator i, iend;
        iend = mSupportedTechniques.end();
        for (i = mSupportedTechniques.begin(); i != iend; ++i)
        {
            (*i)->_prepare();
        }
    }
