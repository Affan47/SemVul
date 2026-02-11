ut_print_charsets () {

	int i; for (i=0; i < ut_session->nb_charsets; i++) {
		printf ("%2d: %20s %2d [", i, ut_session->charset[i].name, ut_session->charset[i].type);
		int j; for (j=0; j<ut_session->language.n_max;j++) printf("%d ",(int)ut_session->charset[i].language[j]);
		printf("] [");
		for (j=0; j<ut_session->system.n_max;j++) printf("%d ",(int)ut_session->charset[i].system[j]);
		printf("]\n");
	}


}
