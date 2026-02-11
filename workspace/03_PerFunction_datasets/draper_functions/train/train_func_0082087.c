_setSceneBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendOperation op )
    {
        GLint sourceBlend = getBlendMode(sourceFactor);
        GLint destBlend = getBlendMode(destFactor);
        if(sourceFactor == SBF_ONE && destFactor == SBF_ZERO)
        {
            mStateCacheManager->setEnabled(GL_BLEND, false);
        }
        else
        {
            mStateCacheManager->setEnabled(GL_BLEND, true);
            mStateCacheManager->setBlendFunc(sourceBlend, destBlend);
        }

        GLint func = GL_FUNC_ADD;
        switch(op)
        {
        case SBO_ADD:
            func = GL_FUNC_ADD;
            break;
        case SBO_SUBTRACT:
            func = GL_FUNC_SUBTRACT;
            break;
        case SBO_REVERSE_SUBTRACT:
            func = GL_FUNC_REVERSE_SUBTRACT;
            break;
        case SBO_MIN:
            func = GL_MIN;
            break;
        case SBO_MAX:
            func = GL_MAX;
            break;
        }

        mStateCacheManager->setBlendEquation(func);
    }
