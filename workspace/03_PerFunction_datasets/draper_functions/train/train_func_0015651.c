forget_traps()
{
	register struct trap *trap;


	for (trap = ftrap; trap; trap = trap->ntrap)
	    if ((trap->tx != u.ux || trap->ty != u.uy) && (trap->ttyp != HOLE))
		trap->tseen = 0;
}
