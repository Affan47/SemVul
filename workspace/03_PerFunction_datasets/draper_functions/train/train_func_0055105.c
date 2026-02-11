compile()
{

    mSupportedTechniques.clear();
    Techniques::iterator i, iend;
    iend = mTechniques.end();


    for (i = mTechniques.begin(); i != iend; ++i)
    {

        if((*i)->isSupported(false))
        {
            mSupportedTechniques.push_back(*i);
        }
    }

    if (mSupportedTechniques.empty())
    {

        for (i = mTechniques.begin(); i != iend; ++i)
        {

            if((*i)->isSupported(true))
            {
                mSupportedTechniques.push_back(*i);
            }
        }
    }

    mCompilationRequired = false;
}
