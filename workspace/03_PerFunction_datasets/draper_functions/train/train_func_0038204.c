PrintBuiltInNodes(u32 graph_type)
{
#if !defined(GPAC_DISABLE_VRML) && !defined(GPAC_DISABLE_X3D) && !defined(GPAC_DISABLE_SVG)
	GF_Node *node;
	GF_SceneGraph *sg;
	u32 i, nb_in, nb_not_in, start_tag, end_tag;

	if (graph_type==1) {
#if !defined(GPAC_DISABLE_VRML) && !defined(GPAC_DISABLE_X3D)
                start_tag = GF_NODE_RANGE_FIRST_X3D;
                end_tag = TAG_LastImplementedX3D;
#else
		fprintf(stderr, "X3D scene graph disabled in this build of GPAC\n");
		return;
#endif
	} else if (graph_type==2) {
#ifdef GPAC_DISABLE_SVG
		fprintf(stderr, "SVG scene graph disabled in this build of GPAC\n");
		return;
#else
		start_tag = GF_NODE_RANGE_FIRST_SVG;
		end_tag = GF_NODE_RANGE_LAST_SVG;
#endif
	} else {
#ifdef GPAC_DISABLE_VRML
		fprintf(stderr, "VRML/MPEG-4 scene graph disabled in this build of GPAC\n");
		return;
#else
		start_tag = GF_NODE_RANGE_FIRST_MPEG4;
		end_tag = TAG_LastImplementedMPEG4;
#endif
	}
	nb_in = nb_not_in = 0;
	sg = gf_sg_new();

	if (graph_type==1) {
		fprintf(stderr, "Available X3D nodes in this build (dumping):\n");
	} else if (graph_type==2) {
		fprintf(stderr, "Available SVG nodes in this build (dumping and LASeR coding):\n");
	} else {
		fprintf(stderr, "Available MPEG-4 nodes in this build (encoding/decoding/dumping):\n");
	}
	for (i=start_tag; i<end_tag; i++) {
		node = gf_node_new(sg, i);
		if (node) {
			gf_node_register(node, NULL);
			fprintf(stderr, " %s\n", gf_node_get_class_name(node));
			gf_node_unregister(node, NULL);
			nb_in++;
		} else {
			if (graph_type==2)
				break;
			nb_not_in++;
		}
	}
	gf_sg_del(sg);
	if (graph_type==2) {
		fprintf(stderr, "\n%d nodes supported\n", nb_in);
	} else {
		fprintf(stderr, "\n%d nodes supported - %d nodes not supported\n", nb_in, nb_not_in);
	}
#else
	fprintf(stderr, "\nNo scene graph enabled in this MP4Box build\n");
#endif
}
