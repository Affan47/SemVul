signame_list(void)
{
	int i, sigrtmax, j, min, max;

	sigrtmax = sigrt_minmax(&min, &max);
	j = 1;

        for (i = 1; i <= sigrtmax; i++) {
		if ((i == SIGRTMIN) || (i == sigrtmax)) {
			fprintf(fp, "[%d] %s", i,
			    (i== SIGRTMIN) ? "SIGRTMIN" : "SIGRTMAX");
		} else if (i > SIGRTMIN) {
			if (j <= min){
				fprintf(fp, "[%d] %s%d", i , "SIGRTMIN+", j);
				j++;
			} else if (max >= 1) {
				fprintf(fp, "[%d] %s%d", i , "SIGRTMAX-",max);
				max--;
			}
		} else {
                	if (!signame[i].name)
                        	continue;

                	fprintf(fp, "%s[%d] %s", i < 10 ? " " : "",
				i, signame[i].name);
			if (signame[i].altname)
				fprintf(fp, "/%s",  signame[i].altname);
		}
		fprintf(fp, "\n");
        }
}
