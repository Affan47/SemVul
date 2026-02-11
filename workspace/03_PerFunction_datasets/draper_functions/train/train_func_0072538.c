check_version(version_data, filename, complain)
struct version_info *version_data;
const char *filename;
boolean complain;
{
	if (
#ifdef VERSION_COMPATIBILITY
	    version_data->incarnation < VERSION_COMPATIBILITY ||
	    version_data->incarnation > VERSION_NUMBER
#else
	    version_data->incarnation != VERSION_NUMBER
#endif
	  ) {
	    if (complain)
		pline("Version mismatch for file \"%s\".", filename);
	    return FALSE;
	} else if (
#ifndef IGNORED_FEATURES
		   version_data->feature_set != VERSION_FEATURES ||
#else
		   (version_data->feature_set & ~IGNORED_FEATURES) !=
			  (VERSION_FEATURES & ~IGNORED_FEATURES) ||
#endif
		   version_data->entity_count != VERSION_SANITY1 ||
		   version_data->struct_sizes != VERSION_SANITY2) {
	    if (complain)
		pline("Configuration incompatibility for file \"%s\".",
		      filename);
	    return FALSE;
	}
	return TRUE;
}
