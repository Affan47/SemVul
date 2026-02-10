gretl_model_test_print_direct (const ModelTest *test, int heading, PRN *prn)
{
    const char *tstr;
    char buf[512];

    set_alt_gettext_mode(prn);

    if (rtf_format(prn)) {
	pputs(prn, "\\par \\ql ");
    }

    if (heading) {
	gretl_test_print_heading(test, prn);
    }

    gretl_test_print_h_0(test, heading, prn);

    tstr = asy_test(test->teststat)? N_("Asymptotic test statistic") :
	N_("Test statistic");

    get_test_stat_string(test, buf, prn);

    if (plain_format(prn)) {
	pprintf(prn, "\n  %s: %s\n", _(tstr), buf);
    } else if (tex_format(prn)) {
	pprintf(prn, "\\\\\n\\quad %s: %s\\\\\n", I_(tstr), buf);
    } else if (rtf_format(prn)) {
	pprintf(prn, "\\par\n %s: %s\\par\n", I_(tstr), buf);
    }

    get_test_pval_string(test, buf, prn);

    if (*buf != '\0') {
	const char *pvstr = asy_pval(test->teststat) ?
	    N_("with asymptotic p-value") : N_("with p-value");

	if (plain_format(prn)) {
	    pprintf(prn, "  %s = %s\n\n", _(pvstr), buf);
	} else if (tex_format(prn)) {
	    pprintf(prn, "\\quad %s = %s\\\\\n", A_(pvstr), buf);
	} else if (rtf_format(prn)) {
	    pprintf(prn, " %s = %s\\par\n\n", A_(pvstr), buf);
	}
    } else if (!na(test->crit) && !na(test->alpha)) {
	double a = test->alpha * 100.0;

	if (plain_format(prn)) {
	    sprintf(buf, _("%g percent critical value"), a);
	    pprintf(prn, "  (%s = %.2f)\n\n", buf, test->crit);
	} else if (tex_format(prn)) {
	    sprintf(buf, A_("%g percent critical value"), a);
	    pprintf(prn, "\\quad (%s = %.2f)\\\\\n", buf, test->crit);
	} else if (rtf_format(prn)) {
	    sprintf(buf, A_("%g percent critical value"), a);
	    pprintf(prn, " (%s = %.2f)\\par\n\n", buf, test->crit);
	}
    } else {
	pputc(prn, '\n');
    }
}
