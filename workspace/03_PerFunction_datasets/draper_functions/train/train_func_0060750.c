croisement_con_alim(ptcoor, concoeur, ptalim)
PT_COORDONNEES ptcoor;
LST_PSEUDO_CON concoeur;
chain_list     *ptalim;
{
	PT_COORDONNEES lst_coor;
	LST_PSEUDO_CON con;
	long	position = 0, positioncour = 0, dminmetalmetal = 0, diff = 0;
	long	widthcour    = concoeur->largeur;
	int	i, nbcolatrouver;

	if (mode_debug)
		printf("\tCroisement con avec alim  %s larg %ld face %ld x %ld y %ld\n", concoeur->nom_con, concoeur->largeur,
		     concoeur->face, ptcoor->xabs, ptcoor->yabs);

	nbcolatrouver = (concoeur->largeur + pitch) / (2 * pitch);


	lst_coor = ptcoor->suiv;
	for (i = 0; i < nbcolatrouver; i++) {
		if ((NULL != lst_coor) && (NULL == lst_coor->proprio))
			lst_coor = lst_coor->suiv;
		else
			return ((long) 1);
	}

	lst_coor = ptcoor->prec;
	for (i = 0; i < nbcolatrouver; i++) {
		if ((NULL != lst_coor) && (NULL == lst_coor->proprio))
			lst_coor = lst_coor->prec;
		else
			return ((long) 1);
	}

	switch (concoeur->face) {
	case NORD:
	case SUD :
		positioncour = ptcoor->xabs;
		dminmetalmetal = ymetal_dmin;
		break;
	case EST  :
	case OUEST:
		positioncour = ptcoor->yabs;
		dminmetalmetal = xmetal_dmin;
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

			diff = distance_con_con(position, position, con->largeur, concoeur->layer, positioncour, positioncour,
			     widthcour, concoeur->layer, concoeur->face);

			if ((diff < 0) || (diff < dminmetalmetal))
				if (mode_debug)
					printf("\tposition cour %ld nom %s position %ld ***diffcrois %ld larg %ld\n", positioncour,
					     con->nom_con, position, diff, con->largeur);

			if (diff < 0)
				return((long) -diff);
			if (diff < dminmetalmetal)
				return ((long) pitch);

		}

		ptalim = ptalim->NEXT;
	}

	return((long) 0);
}
