sgi_set_bootfile(const char* aFile) {

	if (sgi_check_bootfile(aFile)) {
		size_t i = 0;
		while (i < 16) {
			if ((aFile[i] != '\n')
			    &&  (strlen(aFile) > i))
				sgilabel->boot_file[i] = aFile[i];
			else
				sgilabel->boot_file[i] = 0;
			i++;
		}
		printf(_("\n\tBootfile is changed to \"%s\".\n"),
		       sgilabel->boot_file);
	}
}
