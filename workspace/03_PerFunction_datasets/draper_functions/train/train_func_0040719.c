cell_foreach_single_dep (Sheet const *sheet, int col, int row,
			 GnmDepFunc func, gpointer user)
{
	DependencySingle lookup, *single;
	GnmDepContainer *deps = sheet->deps;

	lookup.pos.col = col;
	lookup.pos.row = row;

	single = g_hash_table_lookup (deps->single_hash, &lookup);
	if (single != NULL)
		micro_hash_foreach_dep (single->deps, dep,
			(*func) (dep, user););
}
