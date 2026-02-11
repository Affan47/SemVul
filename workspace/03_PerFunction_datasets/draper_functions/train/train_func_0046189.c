suggest_ondemand_governor(void)
{
	DIR *dir;
	struct dirent *dirent;
	FILE *file;
	char filename[PATH_MAX];
	char line[1024];

	char gov[1024];
	int ret = 0;


	gov[0] = 0;


	dir = opendir("/sys/devices/system/cpu");
	if (!dir)
		return;

	while ((dirent = readdir(dir))) {
		if (dirent->d_name[0]=='.')
			continue;
		sprintf(filename, "/sys/devices/system/cpu/%s/cpufreq/scaling_governor", dirent->d_name);
		file = fopen(filename, "r");
		if (!file)
			continue;
		memset(line, 0, 1024);
		if (fgets(line, 1023,file)==NULL) {
			fclose(file);
			continue;
		}
		if (strlen(gov)==0)
			strcpy(gov, line);
		else

			if (strcmp(gov, line))
				ret = 1;
		fclose(file);
	}

	closedir(dir);


	if (strstr(gov, "userspace"))
		ret = 1;


	if (strstr(gov, "performance"))
		ret = 1;


	if (ret) {
		add_suggestion(_("Suggestion: Enable the ondemand cpu speed governor for all processors via: \n"
				 " echo ondemand > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor \n"),
				15, 'O', _(" O - enable Ondemand governor "), activate_ondemand);
	}
}
