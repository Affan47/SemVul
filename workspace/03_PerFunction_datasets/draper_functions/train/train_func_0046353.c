gf_term_node_callback(void *_is, u32 type, GF_Node *n, void *param)
{
	switch (type) {
	case GF_SG_CALLBACK_MODIFIED:
		gf_term_on_node_modified(_is, n);
		break;
	case GF_SG_CALLBACK_INIT:
		gf_term_on_node_init(_is, n);
		break;

	case GF_SG_CALLBACK_GRAPH_DIRTY:
	{
		u32 i=0;
		GF_Node *root;
		GF_Scene *scene = (GF_Scene *)_is;
		if (scene->root_od->mo) {
			while ((root=(GF_Node*)gf_list_enum(scene->root_od->mo->nodes, &i))) {
				gf_node_dirty_set(root, GF_SG_CHILD_DIRTY, 1);
			}
		}
	}
		break;
	}
}
