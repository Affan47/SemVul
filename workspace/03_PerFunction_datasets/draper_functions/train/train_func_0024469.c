treeStats(
	ostream		&out,
	ANNbool		verbose)
{
	const int	MIN_PTS		= 20;
	const float MAX_FRAC_TL = 0.50;
	const float MAX_AVG_AR	= 20;

	ANNkdStats st;

	the_tree->getStats(st);

	int n_nodes = st.n_lf + st.n_spl + st.n_shr;

	int opt_n_nodes = (int) (2*(float(st.n_pts)/st.bkt_size));
	int too_many_nodes = 10*opt_n_nodes;
	if (st.n_pts >= MIN_PTS && n_nodes > too_many_nodes) {
		out << "-----------------------------------------------------------\n";
		out << "Warning: The tree has more than 10x as many nodes as points.\n";
		out << "You may want to consider a different split or shrink method.\n";
		out << "-----------------------------------------------------------\n";
		verbose = ANNtrue;
	}

	float frac_tl = (st.n_lf == 0 ? 0 : ((float) st.n_tl)/ st.n_lf);
	if (st.n_pts >= MIN_PTS && frac_tl > MAX_FRAC_TL) {
		out << "-----------------------------------------------------------\n";
		out << "Warning: A significant fraction of leaves contain no points.\n";
		out << "You may want to consider a different split or shrink method.\n";
		out << "-----------------------------------------------------------\n";
		verbose = ANNtrue;
	}

	int too_many_levels = (int) (2.0 * st.dim * log2((double) st.n_pts));
	int opt_levels = (int) log2(double(st.n_pts)/st.bkt_size);
	if (st.n_pts >= MIN_PTS && st.depth > too_many_levels) {
		out << "-----------------------------------------------------------\n";
		out << "Warning: The tree is more than 2x as deep as (dim*log n).\n";
		out << "You may want to consider a different split or shrink method.\n";
		out << "-----------------------------------------------------------\n";
		verbose = ANNtrue;
	}

	if (st.n_pts >= MIN_PTS && st.avg_ar > MAX_AVG_AR) {
		out << "-----------------------------------------------------------\n";
		out << "Warning: Average aspect ratio of cells is quite large.\n";
		out << "This may slow queries depending on the point distribution.\n";
		out << "-----------------------------------------------------------\n";
		verbose = ANNtrue;
	}


	if (verbose) {
		out << "  (Structure Statistics:\n";
		out << "    n_nodes          = " << n_nodes
			<< " (opt = " << opt_n_nodes
			<< ", best if < " << too_many_nodes << ")\n"
			<< "        n_leaves     = " << st.n_lf
			<< " (" << st.n_tl << " contain no points)\n"
			<< "        n_splits     = " << st.n_spl << "\n"
			<< "        n_shrinks    = " << st.n_shr << "\n";
		out << "    empty_leaves     = " << frac_tl*100
			<< " percent (best if < " << MAX_FRAC_TL*100 << " percent)\n";
		out << "    depth            = " << st.depth
			<< " (opt = " << opt_levels
			<< ", best if < " << too_many_levels << ")\n";
		out << "    avg_aspect_ratio = " << st.avg_ar
			<< " (best if < " << MAX_AVG_AR << ")\n";
		out << "  )\n";
	}
}
