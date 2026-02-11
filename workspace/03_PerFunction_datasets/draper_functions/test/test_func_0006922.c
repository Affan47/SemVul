poseseg_colonnes(long piste_cour[NB_FACES], LST_EQUIPO equipo,
	LST_SEGMENT segx_occ[NB_FACES], LST_SEGMENT segy_occ[NB_FACES])
{

	PT_COORDONNEES debut_coor;
	LST_PSEUDO_CON con;
	LST_SEGMENT    * segcol = NULL;
	long	largeurmin = 0, largeurvia = 0, largeurseg = 0;
	char	metalcol = 0;
	ptype_list     * lst_proj;

	lst_proj = (equipo->cour).lst_projetes;

	while (NULL != lst_proj) {
		con = (LST_PSEUDO_CON) ((PT_COORDONNEES)lst_proj->DATA)->proprio;
		if (NULL == con)
			ringerreur(ERR_INTERNE_EQ, NULL, NULL);
		debut_coor = (PT_COORDONNEES) lst_proj->DATA;

		switch (con->face) {
		case SUD :
		case NORD:
			segcol = segy_occ;
			metalcol = ymetal;
			largeurmin = ymetal_width;
			largeurvia = ymetal_wvia;
			break;
		case EST  :
		case OUEST:
			segcol = segx_occ;
			metalcol = xmetal;
			largeurvia = xmetal_wvia;
			largeurmin = xmetal_width;
			break;
		}

		if (segment_libre(debut_coor, debut_coor, debut_coor->piste, piste_cour[con->face], con->face, SEG_COL, segcol,
		     metalcol)) {
			if (con->largeur > largeurvia)
				largeurseg = largeurvia;
			else if (con->largeur < largeurmin)
				largeurseg = largeurmin;
			else
				largeurseg = con->largeur;

			alloue_etchaine_segment(debut_coor, debut_coor, debut_coor->piste, piste_cour[con->face], con->face,
			     SEG_COL, segcol, largeurseg, metalcol, VRAI_SEG, AVEC_VIA, equipo);
		}  else
			ringerreur(ERR_NOCOL, (void * )con, NULL);

		lst_proj = lst_proj->NEXT;
	}

}
