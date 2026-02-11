list_genocided(defquery, ask)
char defquery;
boolean ask;
{
    register int i;
    int ngenocided;
    char c;
    winid klwin;
    char buf[BUFSZ];

    ngenocided = num_genocides();


    if (ngenocided != 0) {
	c = ask ? yn_function("SUBJECT MODIFIER_KONJUNKTIV_II VERB_MOEGEN PRONOMEN_PERSONAL eine Liste aller ausgerotteten Arten sehen?",
			      ynqchars, defquery) : defquery;
	if (c == 'q') done_stopprint++;
	if (c == 'y') {
	    klwin = create_nhwindow(NHW_MENU);
	    putstr(klwin, 0, "Ausgerottete Arten:");
	    putstr(klwin, 0, "");

	    for (i = LOW_PM; i < NUMMONS; i++)
		if (mvitals[i].mvflags & G_GENOD) {
		    if ((mons[i].geno & G_UNIQ) && i != PM_HIGH_PRIEST)
			Sprintf(buf, "%s%s",
				!type_is_pname(&mons[i]) ? "" : "the ",
				mons[i].mname);
		    else
			Strcpy(buf, makeplural(mons[i].mname));
		    putstr(klwin, 0, buf);
		}

	    putstr(klwin, 0, "");
	    Sprintf(buf, "%d Art%s ausgerottet.", ngenocided, (ngenocided > 1) ? "en" : "");
	    putstr(klwin, 0, buf);

	    display_nhwindow(klwin, TRUE);
	    destroy_nhwindow(klwin);
	}
    }
}
