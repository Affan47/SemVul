display_svg_tree_orthogonal(struct rooted_tree *tree,
		struct h_data hd, int align_leaves, int with_scale_bar,
		char *branch_length_unit)
{
	double h_scale = -1;


	double v_scale = leaf_vskip;

	if (0.0 == hd.d_max) { hd.d_max = 1; }
	h_scale = (graph_width
			- label_char_width * hd.l_max
			- ROOT_SPACE
			- label_space
		) / hd.d_max;


	printf( "<g"
		" transform='translate(0,%d)'"
		">", whole_v_shift);


	draw_branches_ortho(tree, h_scale, v_scale, align_leaves, hd.d_max);

	draw_text_ortho(tree, h_scale, v_scale, align_leaves, hd.d_max);

	if (with_scale_bar) {
		double scalebar_vpos = (double) graph_height(leaf_count(tree),
				with_scale_bar) - whole_v_shift;
		draw_scale_bar(ROOT_SPACE, scalebar_vpos, h_scale, hd.d_max,
			branch_length_unit);
	}
	printf ("</g>");
}
