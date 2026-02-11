is_superior_fdp( FDP *fdp, const int a, const int b )
{
	if ( !is_empty(fdp->table[a]) && !is_empty(fdp->table[b]) )
		return is_superior_simplex(fdp->table[a], fdp->table[b]);
	else if ( !is_empty(fdp->table[a]) )
		return 1;
	else
		return 0;
}
