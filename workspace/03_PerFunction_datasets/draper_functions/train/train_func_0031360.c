embComWriteFile(AjPFile fp, ajint jmin, ajint jmax,
		     ajint lwin, ajint step, ajint sim)
{

    ajFmtPrintF(fp,"Length of window : %d \n",lwin);
    ajFmtPrintF(fp,"jmin : %d \n",jmin);
    ajFmtPrintF(fp,"jmax : %d \n",jmax);
    ajFmtPrintF(fp,"step : %d \n",step);

    if(sim)
	ajFmtPrintF(fp,"sim : %d \n",sim);

    if(sim == 0)
	ajFmtPrintF(fp,"Execution without simulation \n");

    ajFmtPrintF(fp,"---------------------------------------"
		"-------------------------------------\n");
    ajFmtPrintF(fp,"|                  |                  |"
		"                  |                  |\n");
    ajFmtPrintF(fp,"|     number of    |      name of     |"
		"     length of    |      value of    |\n");
    ajFmtPrintF(fp,"|     sequence     |     sequence     |"
		"     sequence     |     complexity   |\n");
    ajFmtPrintF(fp,"|                  |                  |"
		"                  |                  |\n");
    ajFmtPrintF(fp,"---------------------------------------"
		"-------------------------------------\n");

    return;
}
