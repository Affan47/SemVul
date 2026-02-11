subtree_contraction_enter(
	__isl_take isl_schedule_node *node, void *user)
{
	struct isl_subtree_contraction_data *data = user;

	do {
		enum isl_schedule_node_type type;
		isl_union_set *filter;
		isl_union_pw_multi_aff *inner, *contraction;
		int n;

		switch (isl_schedule_node_get_type(node)) {
		case isl_schedule_node_error:
			return isl_schedule_node_free(node);
		case isl_schedule_node_filter:
			type = isl_schedule_node_get_parent_type(node);
			if (type != isl_schedule_node_set &&
			    type != isl_schedule_node_sequence)
				break;
			filter = isl_schedule_node_filter_get_filter(node);
			n = isl_union_pw_multi_aff_list_n_union_pw_multi_aff(
						data->contractions);
			inner =
			    isl_union_pw_multi_aff_list_get_union_pw_multi_aff(
						data->contractions, n - 1);
			inner = isl_union_pw_multi_aff_intersect_domain(inner,
								filter);
			data->contractions =
			    isl_union_pw_multi_aff_list_add(data->contractions,
								inner);
			break;
		case isl_schedule_node_expansion:
			n = isl_union_pw_multi_aff_list_n_union_pw_multi_aff(
						data->contractions);
			contraction =
			    isl_schedule_node_expansion_get_contraction(node);
			inner =
			    isl_union_pw_multi_aff_list_get_union_pw_multi_aff(
						data->contractions, n - 1);
			inner =
			    isl_union_pw_multi_aff_pullback_union_pw_multi_aff(
						inner, contraction);
			data->contractions =
			    isl_union_pw_multi_aff_list_set_union_pw_multi_aff(
					data->contractions, n - 1, inner);
			break;
		case isl_schedule_node_band:
		case isl_schedule_node_context:
		case isl_schedule_node_domain:
		case isl_schedule_node_extension:
		case isl_schedule_node_guard:
		case isl_schedule_node_leaf:
		case isl_schedule_node_mark:
		case isl_schedule_node_sequence:
		case isl_schedule_node_set:
			break;
		}
	} while (isl_schedule_node_has_children(node) &&
		(node = isl_schedule_node_first_child(node)) != NULL);

	return node;
}
