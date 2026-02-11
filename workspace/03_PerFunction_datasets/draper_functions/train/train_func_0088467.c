read_type_form(FILE * fp)
{
    chasen_cell_t *cell1, *cell2;
    int i, j;
    char *s;

    for (i = 1; !cha_s_feof(fp); i++) {
	cell1 = cha_s_read(fp);
	Cha_type[i].name = cha_strdup(cha_s_atom(cha_car(cell1)));
	Cha_type[i].basic = 0;
	cell1 = cha_car(cha_cdr(cell1));


	if (cha_litmatch(Cha_type[i].name, 2,
			 STR_BASE_FORM_STR1, STR_BASE_FORM_STR2)) {
	    Cha_base_form_str = cha_strdup(cha_s_atom(cell1));
	    i--;
	    continue;
	}

	for (j = 1; !nullp(cell2 = cha_car(cell1));
	     cell1 = cha_cdr(cell1), j++) {


	    Cha_form[i][j].name = cha_strdup(cha_s_atom(cha_car(cell2)));
	    if (!Cha_type[i].basic &&
		(Cha_base_form_str
		 ? !strcmp(Cha_form[i][j].name, Cha_base_form_str)
		 : cha_litmatch(Cha_form[i][j].name, 2,
				STR_BASE_FORM1, STR_BASE_FORM2)))
		Cha_type[i].basic = j;


	    if (strcmp
		(s =
		 cha_s_atom(cha_car(cell2 = cha_cdr(cell2))), "*") == 0)
		Cha_form[i][j].gobi = "";
	    else {
		Cha_form[i][j].gobi = cha_strdup(s);
		Cha_form[i][j].gobi_len = strlen(s);
	    }


	    if (nullp(cha_car(cell2 = cha_cdr(cell2))))
		Cha_form[i][j].ygobi = Cha_form[i][j].gobi;
	    else if (strcmp(s = cha_s_atom(cha_car(cell2)), "*") == 0)
		Cha_form[i][j].ygobi = "";
	    else {
		Cha_form[i][j].ygobi = cha_strdup(s);
	    }


	    if (nullp(cha_car(cell2 = cha_cdr(cell2))))
		Cha_form[i][j].pgobi = Cha_form[i][j].ygobi;
	    else if (strcmp(s = cha_s_atom(cha_car(cell2)), "*") == 0)
		Cha_form[i][j].pgobi = "";
	    else {
		Cha_form[i][j].pgobi = cha_strdup(s);
	    }
	}
	if (!Cha_type[i].basic)
	    cha_exit_file(1, "no basic form");
    }
}
