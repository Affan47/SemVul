textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int f,count;
	f = open(fn, O_RDONLY);

	count = lseek(f, 0, SEEK_END);

	close(f);

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {


			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
