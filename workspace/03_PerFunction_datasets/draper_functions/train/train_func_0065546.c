check_is_permutation(t_TEXT *Text, size_t length, int_text n, t_TEXT *t_Aux){


	size_t i, k;

	t_GSA *GSA = (t_GSA*) malloc((BLOCK_ESA_SIZE) * sizeof(t_GSA));
	if(!GSA) perror("is_permutation_GSA");


	int_text y;
	for(y = 0; y < n; y++)
		for (i = 0;  i < Text[y].length;  i++)
			Text[y].c_buffer[i] = 0;

	esa_read_gsa(GSA, BLOCK_ESA_SIZE, t_Aux->f_ESA);

	size_t text[1];
	size_t suff[1];

	for(k = 0; k < length/BLOCK_ESA_SIZE+1; k++){

		for (i = 0;  i < BLOCK_ESA_SIZE;  i++) {

			if(i+(k*BLOCK_ESA_SIZE) == length)
				break;

			#if INPUT_CAT

				text[0] = get_text(Text, n, GSA[i].text);
				suff[0] = get_suff(Text, text[0], GSA[i].text, GSA[i].suff);
			#else

				text[0] = GSA[i].text;
				suff[0] = GSA[i].suff;
			#endif

			Text[text[0]].c_buffer[suff[0]] = 1;


		}

		esa_read_gsa(GSA, BLOCK_ESA_SIZE, t_Aux->f_ESA);
	}

	for(y = 0; y < n; y++)
		for (i = 0;  i < Text[y].length;  i++){

			if (!Text[y].c_buffer[i])
				return 0;
		}

	free(GSA);

return 1;
}
