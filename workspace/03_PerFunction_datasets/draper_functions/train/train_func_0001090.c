build_indexed_triangle_fan_set(GF_Node *node, Drawable3D *stack, GF_TraverseState *tr_state)
{
	MFInt32 fanList;
	u32 i, nb_fans;
	X_IndexedTriangleFanSet *itfs = (X_IndexedTriangleFanSet *)node;
	gf_node_dirty_clear(node, 0);
	if (!itfs->coord) return;

	fanList.count = 0; fanList.vals = NULL;
	nb_fans = 0;
	for (i=0; i<itfs->index.count; i++) {
		if (itfs->index.vals[i]==-1) {
			if (nb_fans>=3) {
				u32 *out_nb;
				gf_sg_vrml_mf_append(&fanList, GF_SG_VRML_MFINT32, (void **) &out_nb);
				*out_nb = nb_fans;
			}
			nb_fans = 0;
		} else {
			nb_fans++;
		}
	}
	if (nb_fans>=3) {
		u32 *out_nb;
		gf_sg_vrml_mf_append(&fanList, GF_SG_VRML_MFINT32, (void **) &out_nb);
		*out_nb = nb_fans;
	}
	BuildTriangleFanSet(stack->mesh, itfs->coord, itfs->color, itfs->texCoord, itfs->normal, &fanList, &itfs->index, itfs->normalPerVertex, itfs->ccw, itfs->solid);
	gf_sg_vrml_mf_reset(&fanList, GF_SG_VRML_MFINT32);
}
