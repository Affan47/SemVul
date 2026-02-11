link_unlink_single_dep (GnmDependent *dep, GnmCellPos const *pos,
			GnmCellRef const *a, gboolean qlink)
{
	return qlink
		? link_single_dep (dep, pos, a)
		: unlink_single_dep (dep, pos, a);
}
