FcConfigAddConfigFile (FcConfig	    *config,
		       const FcChar8   *f)
{
    FcBool	ret;
    FcChar8	*file = FcConfigFilename (f);

    if (!file)
	return FcFalse;

    ret = FcStrSetAdd (config->configFiles, file);
    FcStrFree (file);
    return ret;
}
