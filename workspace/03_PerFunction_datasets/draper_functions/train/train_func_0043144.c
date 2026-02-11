croisementok_alimequi(concoeur, ptalim, testlayer)
LST_PSEUDO_CON concoeur;
chain_list     *ptalim;
char	testlayer;
{
	LST_PSEUDO_CON con;
	long	position = 0, positioncour = 0;
	char	metalcol = 0;

	if (mode_debug)
		printf("\tCroisement con avec alim equi %s larg %ld face %ld x %ld y %ld\n", concoeur->nom_con, concoeur->largeur,
		     concoeur->face, concoeur->coord->xabs, concoeur->coord->yabs);

	switch (concoeur->face) {
	case NORD:
	case SUD :
		positioncour = concoeur->coord->xabs;
		metalcol = ymetal;
		break;
	case EST  :
	case OUEST:
		positioncour = concoeur->coord->yabs;
		metalcol = xmetal;
		break;
	}

	while (ptalim != NULL) {
		con = (LST_PSEUDO_CON) ptalim->DATA;

		if ((con->face == concoeur->face) && (con->coeur_plot != concoeur->coeur_plot)) {
			switch (concoeur->face) {
			case NORD:
			case SUD :
				position = (con->coord)->xabs;
				break;
			case EST  :
			case OUEST:
				position = (con->coord)->yabs;
				break;
			}

			if (mode_debug)
				printf("\tCroisement conplot avec alim equi %s larg %ld face %ld position%ld\n", con->nom_con,
				     con->largeur, con->face, position);

			if (position < positioncour) {
				if (((position + con->largeur / 2) >= positioncour) && ((con->layer == metalcol) || (testlayer)) ) {
					if (mode_debug)
						printf("croisement trouve\n");
					return((long) 1);
				}
			} else if (position > positioncour) {
				if (((position - con->largeur / 2) <= positioncour) && ((con->layer == metalcol) || (testlayer)) ) {
					if (mode_debug)
						printf("croisement trouve\n");
					return((long) 1);
				}
			} else if ((con->layer == metalcol) || (testlayer)) {
				if (mode_debug)
					printf("croisement trouve\n");
				return ((long) 1);
			}
		}

		ptalim = ptalim->NEXT;
	}

	return((long) 0);
}
