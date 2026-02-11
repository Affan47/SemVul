lecture_vues(char *nom_circuit_lo, COEUR *lecoeur, lofig_list **circuit_lo,
	chain_list **liste_plotsph, int	*nbplots, chain_list **lst_conestouest)
{
	chain_list * lstph;
	phfig_list * ptfig;
	loins_list * circuit_inst;
	loins_list * coeur_inst = NULL;
	int	nbcoeur = 0;
	int	retour;

	*circuit_lo = getlofig(nom_circuit_lo, 'A');

	if (!(*circuit_lo))
		ringerreur(ERR_CIRCUITLO, nom_circuit_lo, NULL);


	circuit_inst = (*circuit_lo)->LOINS;

	if (!circuit_inst)
		ringerreur(ERR_CIRCUITINST, nom_circuit_lo, NULL);


	testcon_modelfig(*circuit_lo);


	*nbplots = 0;

	(*liste_plotsph) = NULL;

	while (circuit_inst != NULL) {
		retour = incatalog(circuit_inst->FIGNAME);
		if (mode_debug)
			printf("FIGNAME %s incatalog %d\n", circuit_inst->FIGNAME, retour);

		if (retour) {
			(*nbplots)++;


			ajout_listeplotsph(circuit_inst->FIGNAME, liste_plotsph);
		}  else 		 {
			nbcoeur++;
			coeur_inst = circuit_inst;
		}

		circuit_inst = circuit_inst->NEXT;
	}

	if (mode_debug)
		printf("Lirevues: nb inst plots %d\n", *nbplots);


	switch (nbcoeur) {
	case 0:
		ringerreur(ERR_NONCOEUR, NULL, NULL);
		break;

	case 1:


		(*lecoeur).coeur_lo = coeur_inst;
		if ((*lecoeur).coeur_lo == NULL)
			ringerreur(ERR_COEURINSTLO, coeur_inst->FIGNAME, NULL);

		ptfig = (*lecoeur).coeur_ph = getphfig(coeur_inst->FIGNAME, 'A');
		(*lecoeur).coord.xabs = 0;
		(*lecoeur).coord.yabs = 0;
		(*lecoeur).width = ptfig->XAB2 - ptfig->XAB1;
		(*lecoeur).height = ptfig->YAB2 - ptfig->YAB1;
		(*lecoeur).coord.piste = 0;

		(*lecoeur).rotation = NOSYM;


		if ((*lecoeur).coeur_ph == NULL)
			ringerreur(ERR_COEURINSTPH, coeur_inst->FIGNAME, NULL);

		break;
	default:


		ringerreur(ERR_PLUSCOEUR, (*circuit_lo)->LOINS, NULL);
	}


	lstph = *liste_plotsph;

	while (NULL != lstph) {
		verif_con_estouest(lstph, lst_conestouest);
		lstph = lstph->NEXT;
	}

	if (mode_debug)
		affic_listeplotsph(*liste_plotsph);

}
