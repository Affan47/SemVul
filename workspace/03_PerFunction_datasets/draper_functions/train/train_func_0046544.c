maj_stat_vias(LST_EQUIPO eq, long ancr, long ancp, long r, long p)
{

	if (mode_debug)
		eq->status.nb_vias += (r - ancr);
	else
		eq->status.nb_vias += (p - ancp);
}
