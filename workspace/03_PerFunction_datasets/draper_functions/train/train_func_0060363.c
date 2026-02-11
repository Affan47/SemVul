getFBConfigFromContext(::GLXContext context)
    {
        GLXFBConfig fbConfig = 0;

        int fbConfigAttrib[] = {
            GLX_FBCONFIG_ID, 0,
            None
        };
        GLXFBConfig *fbConfigs;
        int nElements = 0;

        glXQueryContext(mGLDisplay, context, GLX_FBCONFIG_ID, &fbConfigAttrib[1]);
        fbConfigs = glXChooseFBConfig(mGLDisplay, DefaultScreen(mGLDisplay), fbConfigAttrib, &nElements);

        if (nElements)
        {
            fbConfig = fbConfigs[0];
            XFree(fbConfigs);
        }

        return fbConfig;
    }
