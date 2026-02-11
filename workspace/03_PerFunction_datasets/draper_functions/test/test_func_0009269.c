multi_menu()
{
	if(dnaflag) {
		gap_open   = dna_gap_open;
		gap_extend = dna_gap_extend;
	}
	else {
		gap_open   = prot_gap_open;
		gap_extend = prot_gap_extend;
	}

	while(TRUE) {
		lin3 = is_weight ? "Weighted" :"Unweighted";

		fprintf(stdout,"\n\n\n");
		fprintf(stdout," ********* MYERS/MILLER MULTIPLE ALIGNMENT PARAMETERS *********\n");
		fprintf(stdout,"\n\n");

		fprintf(stdout,"     1. Fixed Gap Penalty       :%d\n",gap_open);
		fprintf(stdout,"     2. Floating Gap Penalty    :%d\n",gap_extend);
		fprintf(stdout,"     3. Toggle Transitions (DNA):%s\n",lin3);
		fprintf(stdout,"     4. Protein weight matrix   :%s\n\n"
					,pam_matrix_name[matnum-1]);
		fprintf(stdout,"     H. HELP\n\n\n");

		getstr("Enter number (or [RETURN] to exit)",lin2);

		if(*lin2 == EOS) {
			if(dnaflag) {
				dna_gap_open    = gap_open;
				dna_gap_extend  = gap_extend;
			}
			else {
				prot_gap_open   = gap_open;
				prot_gap_extend = gap_extend;
			}
			return;
		}

		switch(toupper(*lin2)) {
			case '1':
			fprintf(stdout,"Fixed Gap Penalty Currently: %d\n",gap_open);
				gap_open=getint("Enter number",1,100,gap_open);
				break;
			case '2':
				fprintf(stdout,"Floating Gap Penalty Currently: %d\n",gap_extend);
				gap_extend=getint("Enter number",1,100,gap_extend);
				break;
			case '3':
				is_weight ^= TRUE;
				break;
			case '4':
				read_matrix();
				break;
			case '?':
			case 'H':
				get_help(4);
				break;
			default:
				fprintf(stderr,"\n\nUnrecognised Command\n\n");
				break;
		}
	}
}
