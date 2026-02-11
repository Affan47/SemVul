setSceneBlending( const SceneBlendFactor sourceFactor,
        const SceneBlendFactor destFactor)
    {
        Techniques::iterator i, iend;
        iend = mTechniques.end();
        for (i = mTechniques.begin(); i != iend; ++i)
        {
            (*i)->setSceneBlending(sourceFactor, destFactor);
        }
    }
