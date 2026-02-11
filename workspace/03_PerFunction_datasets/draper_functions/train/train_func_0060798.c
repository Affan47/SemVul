madwifing_list_vaps(const char *ifname, vector<string> *retvec) {
	DIR *devdir;
	struct dirent *devfile;
	string dirpath;
	int kern24model = 0;
	FILE *pf = NULL;

	dirpath = "/sys/class/net/" + string(ifname) + "/device/";

	if ((devdir = opendir(dirpath.c_str())) == NULL) {
		dirpath = "/proc/sys/net/";
		if ((devdir = opendir(dirpath.c_str())) == NULL) {
			return -1;
		}
		kern24model = 1;
	}

	while ((devfile = readdir(devdir)) != NULL) {
		if (kern24model) {
			string pfname = dirpath + devfile->d_name + "/%parent";
			char pname[64];

			if ((pf = fopen(pfname.c_str(), "r")) == NULL) {
				continue;
			} else {
				if (fscanf(pf, "%s", pname) != 1) {
					fclose(pf);
					continue;
				} else {
					retvec->push_back(devfile->d_name);
				}

				fclose(pf);
			}
		} else {
			string ownername = "net:" + string(ifname);

			if (strncmp("net:", devfile->d_name, 4) == 0)
				retvec->push_back(devfile->d_name + 4);
		}
	}

	closedir(devdir);

	return retvec->size();
}
