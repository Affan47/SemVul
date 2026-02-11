menu(char* dir) {
	struct dirent **directories;
	char *next_dir;
	int num_dir, count;


	if(dir != NULL) {
		next_dir = strchr(dir,'/');
		if(next_dir != NULL)
			*next_dir = '\0';
	}


	num_dir = scandir(".",&directories,isdir,alphasort);
	if(num_dir > 0) {
		fputs("<ul>\n",stdout);
		for(count = 0; count < num_dir;count++) {
			fputs("\t<li><a href=\"",stdout);
			fputs(mainfile,stdout);
			fputs(directories[count]->d_name,stdout);
			fputs("\">",stdout);
			fputs(directories[count]->d_name,stdout);
			fputs("</a></li>\n",stdout);


			if(dir != NULL && strcmp(dir,directories[count]->d_name) == 0) {
				chdir(dir);
				if(next_dir != NULL) {
					next_dir++;
				}
				menu(next_dir);
			}
		}
		fputs("</ul>\n",stdout);
	}
	return 0;
}
