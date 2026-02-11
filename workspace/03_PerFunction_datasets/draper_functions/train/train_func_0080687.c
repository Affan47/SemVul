set_cfg_option(char *opt_string)
{
	char *sep, *sep2, szSec[1024], szKey[1024], szVal[1024];
	sep = strchr(opt_string, ':');
	if (!sep) {
		fprintf(stderr, "Badly formatted option %s - expected Section:Name=Value\n", opt_string);
		return;
	}
	sep[0] = 0;
	strcpy(szSec, opt_string);
	sep[0] = ':'; sep ++;
	sep2 = strchr(sep, '=');
	if (!sep2) {
		fprintf(stderr, "Badly formatted option %s - expected Section:Name=Value\n", opt_string);
		return;
	}
	sep2[0] = 0;
	strcpy(szKey, sep);
	strcpy(szVal, sep2+1);
	sep2[0] = '=';
	if (!stricmp(szVal, "null")) szVal[0]=0;
	gf_cfg_set_key(cfg_file, szSec, szKey, szVal[0] ? szVal : NULL);
}
