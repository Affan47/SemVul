wind_profile(const char *name, wind_profile_flags *flags)
{
    unsigned int i;

    for (i = 0; i < sizeof(profiles)/sizeof(profiles[0]); i++) {
	if (strcasecmp(profiles[i].name, name) == 0) {
	    *flags = profiles[i].flags;
	    return 0;
	}
    }
    return WIND_ERR_NO_PROFILE;
}
