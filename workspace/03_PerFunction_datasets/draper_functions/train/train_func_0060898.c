pick_version(unsigned char *versions,
	unsigned char requested)
{


	int i;
	char version_num=0;
	char found_version=0;
	struct afp_versions * p;
	char highest=0;

	if (requested)
		requested= min(requested,AFP_MAX_SUPPORTED_VERSION);

	for (i=0;versions[i] && (i<SERVER_MAX_VERSIONS);i++) {
		version_num=versions[i];
		highest=max(highest,version_num);
		if (versions[i]==requested) {
			found_version=1;
			break;
		}
	};

	if (!found_version)
		version_num=highest;

	for (p=afp_versions;p->av_name;p++) {
		if (p->av_number==version_num) {
			return p;
		}
	}
	return NULL;
}
