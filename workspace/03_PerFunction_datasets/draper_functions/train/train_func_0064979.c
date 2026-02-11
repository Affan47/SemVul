tex_print_coeff (const model_coeff *mc, PRN *prn)
{
    char col1[64], col2[64], col3[64], col4[64];
    int ncols = 4;

    if (mc->multi) {
	tex_multi_double(mc->b, col1);
	tex_multi_double(mc->se, col2);
	pprintf(prn, "%s & %s & %s \\\\\n", mc->name, col1, col2);
	return;
    }

    if (use_custom) {
	tex_print_coeff_custom(mc, prn);
	return;
    }

    if (na(mc->b)) {
	sprintf(col1, "\\multicolumn{2}{c}{\\rm %s}", A_("undefined"));
    } else {
	tex_rl_double(mc->b, col1);
    }

    if (!na(mc->lo) && !na(mc->hi)) {
	tex_rl_double(mc->lo, col2);
	tex_rl_double(mc->hi, col3);
	ncols = 3;
    } else {
	if (na(mc->se)) {
	    sprintf(col2, "\\multicolumn{2}{c}{\\rm %s}", A_("undefined"));
	} else {
	    tex_rl_double(mc->se, col2);
	}

	if (na(mc->tval)) {
	    sprintf(col3, "\\multicolumn{2}{c}{\\rm %s}", A_("undefined"));
	} else {
	    tex_rl_float(mc->tval, col3, 4);
	}
    }

    *col4 = '\0';

    if (!mc->show_pval && na(mc->slope)) {
	strcpy(col4, "\\multicolumn{2}{c}{}");
    } else if (!na(mc->slope)) {
	tex_rl_double(mc->slope, col4);
    } else if (mc->show_pval) {
	if (!na(mc->pval)) {
	    tex_rl_float(mc->pval, col4, 4);
	}
    }

    pprintf(prn, "%s &\n"
	    "  %s &\n"
	    "    %s &\n",
	    mc->name,
	    col1,
	    col2);

    if (ncols == 4) {
	pprintf(prn,
		"      %s &\n"
		"        %s \\\\\n",
		col3,
		col4);
    } else {
	pprintf(prn,
		"      %s \\\\\n",
		col3);
    }
}
