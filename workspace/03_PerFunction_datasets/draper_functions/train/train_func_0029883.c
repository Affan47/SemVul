dirty_children(GF_Node *node)
{
	u32 i, count;
	GF_FieldInfo info;
	if (!node) return;

	node->sgprivate->flags &= GF_NODE_INTERNAL_FLAGS;
	if (node->sgprivate->tag>=GF_NODE_RANGE_LAST_VRML) {
		GF_ChildNodeItem *child = ((GF_ParentNode*)node)->children;
		while (child) {
			dirty_children(child->node);
			child = child->next;
		}
	} else {
		count = gf_node_get_field_count(node);
		for (i=0; i<count; i++) {
			gf_node_get_field(node, i, &info);
			if (info.fieldType==GF_SG_VRML_SFNODE) dirty_children(*(GF_Node **)info.far_ptr);
			else if (info.fieldType==GF_SG_VRML_MFNODE) {
				GF_ChildNodeItem *list = *(GF_ChildNodeItem **) info.far_ptr;
				while (list) {
					dirty_children(list->node);
					list = list->next;
				}
			}
		}
	}
}
