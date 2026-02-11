uneseuleoccurence(nom, tab)
char	*nom;
chain_list *tab[NB_FACES];
{

	int	i;
	chain_list * liste;
	char	*nomplot;
	int	cptoccur = 0;

	for (i = 0; i < NB_FACES; i++) {

		liste = tab[i];
		while (liste != NULL) {
			nomplot = (char *)(liste->DATA);

			if (nom == nomplot)
				cptoccur++;
			liste = liste->NEXT;
		}

	}

	if (cptoccur == 1)
		return(1);

	return(0);

}
