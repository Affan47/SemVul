gf_sg_dom_event_bubble(GF_Node *node, GF_DOM_Event *event, GF_List *use_stack, u32 cur_par_idx)
{
	GF_Node *parent;

	if (!node || node->sgprivate->scenegraph->abort_bubbling) return;


	parent = gf_node_get_parent(node, 0);

	if (!parent) {

		if (node->sgprivate->scenegraph->RootNode==node)
			sg_fire_dom_event(&node->sgprivate->scenegraph->dom_evt, event, node->sgprivate->scenegraph, NULL);
		return;
	}
	if (cur_par_idx) {
		GF_Node *used_node = gf_list_get(use_stack, cur_par_idx-1);

		if (used_node==node) {
			parent = gf_list_get(use_stack, cur_par_idx);
			if (cur_par_idx>1) cur_par_idx-=2;
			else cur_par_idx = 0;

			if (parent->sgprivate->interact && !sg_fire_dom_event(parent->sgprivate->interact->dom_evt, event, node->sgprivate->scenegraph, parent)) return;
			gf_sg_dom_event_bubble(parent, event, use_stack, cur_par_idx);
			return;
		}
	}

	if (parent->sgprivate->interact && !sg_fire_dom_event(parent->sgprivate->interact->dom_evt, event, node->sgprivate->scenegraph, parent)) return;
	gf_sg_dom_event_bubble(parent, event, use_stack, cur_par_idx);
}
