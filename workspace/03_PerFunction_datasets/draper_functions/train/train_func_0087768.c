stf_fprint(FILE *fp, struct stf *stf, int level, int col)
{
	int lasttype = 0, l;


	col += fprintf(fp, "( ");


	for (; stf != NULL; stf = stf->next) {
		switch(stf->type) {
		case STFT_SYMBOL:
			if (col > STF_PRINT_RIGHT)
				col = stf_linebreak(fp, level);
			if (level == 0 && col > STF_PRINT_TAB)
				col = stf_linebreak(fp, level);
			col += fprintf(fp, "%s ", symname[STF_SYMBOL(stf)]);
			break;
		case STFT_DOUBLE:
			col += fprintf(fp, "%.12g ", STF_DOUBLE(stf));
			break;
		case STFT_STRING:
			l = strlen(STF_STRING(stf));
			if (col + l > STF_PRINT_COLS)
				col = stf_linebreak(fp, level);
			col += fprintf(fp, "\"%s\" ", STF_STRING(stf));
			break;
		case STFT_IDENT:


			col += fprintf(fp, "%s ", STF_IDENT(stf));
			break;
		case STFT_INT:
			col += fprintf(fp, "%d ", STF_INT(stf));
			break;
		case STFT_UINT:
			col += fprintf(fp, "%ud ", STF_UINT(stf));
			break;
		case STFT_GLIST:
			col = fprint_star_list(fp, STF_GLIST(stf), level);
			break;
		case STFT_LIST:

			col = stf_fprint(fp, STF_LIST(stf), level+1, col);
			break;
		}
		if (stf->next == NULL)
			break;
		if ((stf->type == STFT_LIST && lasttype == STFT_LIST) ) {
			col = stf_linebreak(fp, level);
		}
		lasttype = stf->type;
	}
	if (level == 0) {
		fprintf(fp, ")\n");
		col = 0;
	} else {
		col += fprintf(fp, ") ");
	}

	return col;
}
