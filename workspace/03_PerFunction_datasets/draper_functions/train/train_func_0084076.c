add_replace_file(char *fname)
{
	FILE *f;
	char buf[255], buf1[255], buf2[255];

	if ((f = fopen(fname, "r")) == NULL)
		err(1, "%s", fname);

	while (fgets(buf, 255, f) != NULL) {
		if (strlen(buf) <= 1)
			continue;
		buf1[0] = '\0';
		buf2[0] = '\0';
		sscanf(buf,"%s %s", buf1, buf2);
		if (strlen(buf2) < 1)
			add_identifier(buf1);
		else {


			if (htable_exists(id_table, buf1))
				printf("Identifier %s already defined", buf1);
			else
				htable_store(id_table, buf1, xstrdup(buf2));
		}
        }
	fclose(f);
}
