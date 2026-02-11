poser_segments(LST_EQUIPO lst_equipo, COEUR lecoeur,
	lofig_list *circuit_lo, phfig_list *circuit_ph)
{
	long	ringviasanc = 0, bigviasanc = 0;

	while (NULL != lst_equipo) {
		if (mode_debug)
			printf("Pose des segments MBK des equipotentielles %ld \n", lst_equipo->index);
		poser_segments_eq(lst_equipo, lecoeur, circuit_lo);

		ringviasanc = ringvias;
		bigviasanc = bigvias;
		poser_vias_eq(lst_equipo, lecoeur, circuit_ph);
		if (mode_stat)
			maj_stat_vias(lst_equipo, ringviasanc, bigviasanc, ringvias, bigvias);
		lst_equipo = lst_equipo->suiv;
	}

	if (mode_debug)
		printf("***** VIAS TOTAL %ld VIAS COURONNE %ld ****\n\n", bigvias, ringvias);


}
