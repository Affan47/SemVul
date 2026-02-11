initClass()


{
    SO__NODE_INIT_CLASS(SoSeparator, "Separator", SoGroup);


    SO_ENABLE(SoGetBoundingBoxAction,	SoCacheElement);
    SO_ENABLE(SoGLRenderAction,		SoCacheElement);
    SO_ENABLE(SoGLRenderAction,		SoGLCacheContextElement);


    const char *NRC;
    if ((NRC = getenv("IV_SEPARATOR_MAX_CACHES")) != NULL) {
	numRenderCaches = atoi(NRC);
    }
}
