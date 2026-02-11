poser_blocs(phfig_list **circuit_ph, char *nomcircuit,
	BARRE_PLOTS tab_plots[NB_FACES], COEUR lecoeur)
{
	long	val;
	int	face;

	definir_fig_ph(nomcircuit);


	for (face = 0; face < NB_FACES; face++) {
		if (mode_debug)
			printf("face %d largeur %ld hauteur %ld x %ld y %ld piste %ld width coeur %ld height coeur %ld\n",
			     	        face, tab_plots[face].width, tab_plots[face].height, tab_plots[face].coord.xabs, tab_plots[face].coord.yabs,
			     tab_plots[face].coord.piste, lecoeur.width, lecoeur.height);

		if (0 != tab_plots[face].width) {
			switch (face) {
			case NORD:
				val = (tab_plots[face].coord.piste * pitch + lecoeur.coord.yabs + lecoeur.height) / SCALE_X;
				placer_instph(tab_plots[face].nomfig, tab_plots[face].nominst, NOSYM, (tab_plots[face].coord.xabs
				    / SCALE_X), val);
				break;

			case SUD:
				val = (tab_plots[face].coord.piste * -pitch - tab_plots[face].height + lecoeur.coord.yabs) /
				    SCALE_X;
				placer_instph(tab_plots[face].nomfig, tab_plots[face].nominst, SYM_Y, (tab_plots[face].coord.xabs
				    / SCALE_X), val);
				break;

			case EST:
				val = (tab_plots[face].coord.piste * pitch + lecoeur.coord.xabs + lecoeur.width) / SCALE_X;
				placer_instph(tab_plots[face].nomfig, tab_plots[face].nominst, SY_RP, val, (tab_plots[face].coord.yabs
				    / SCALE_X));
				break;

			case OUEST:
				val = (tab_plots[face].coord.piste * -pitch - tab_plots[face].height + lecoeur.coord.xabs) /
				    SCALE_X;
				placer_instph(tab_plots[face].nomfig, tab_plots[face].nominst, ROT_P, val, (tab_plots[face].coord.yabs
				    / SCALE_X));
				break;
			}
		}
	}


	placer_instph((lecoeur.coeur_ph)->NAME, (lecoeur.coeur_lo)->INSNAME, NOSYM, (lecoeur.coord.xabs / SCALE_X),  (lecoeur.coord.yabs / SCALE_X));


	(*circuit_ph) = getphfig(nomcircuit, 'A');


}
