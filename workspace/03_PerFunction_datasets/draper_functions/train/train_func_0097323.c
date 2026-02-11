_setSeparateSceneBlending(
        SceneBlendFactor sourceFactor, SceneBlendFactor destFactor,
        SceneBlendFactor sourceFactorAlpha, SceneBlendFactor destFactorAlpha,
        SceneBlendOperation op, SceneBlendOperation alphaOp )
    {
        GLint sourceBlend = getBlendMode(sourceFactor);
        GLint destBlend = getBlendMode(destFactor);
        GLint sourceBlendAlpha = getBlendMode(sourceFactorAlpha);
        GLint destBlendAlpha = getBlendMode(destFactorAlpha);

        if(sourceFactor == SBF_ONE && destFactor == SBF_ZERO &&
           sourceFactorAlpha == SBF_ONE && destFactorAlpha == SBF_ZERO)
        {
            mStateCacheManager->setEnabled(GL_BLEND, false);
        }
        else
        {
            mStateCacheManager->setEnabled(GL_BLEND, true);
            if(GLEW_VERSION_1_4)
                glBlendFuncSeparate(sourceBlend, destBlend, sourceBlendAlpha, destBlendAlpha);
            else if(GLEW_EXT_blend_func_separate)
                glBlendFuncSeparateEXT(sourceBlend, destBlend, sourceBlendAlpha, destBlendAlpha);
        }

        GLint func = GL_FUNC_ADD, alphaFunc = GL_FUNC_ADD;

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

        switch(alphaOp)
        {
        case SBO_ADD:
            alphaFunc = GL_FUNC_ADD;
            break;
        case SBO_SUBTRACT:
            alphaFunc = GL_FUNC_SUBTRACT;
            break;
        case SBO_REVERSE_SUBTRACT:
            alphaFunc = GL_FUNC_REVERSE_SUBTRACT;
            break;
        case SBO_MIN:
            alphaFunc = GL_MIN;
            break;
        case SBO_MAX:
            alphaFunc = GL_MAX;
            break;
        }

        mStateCacheManager->setBlendEquation(func, alphaFunc);
    }
