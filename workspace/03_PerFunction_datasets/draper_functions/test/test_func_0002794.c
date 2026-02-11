compositor_init_afx_node(GF_Compositor *compositor, GF_Node *node, MFURL *url)
{
	GF_MediaObject *mo = gf_mo_register(node, url, 0, 0);
	if (!mo) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_COMPOSE, ("[Compositor] AFX Decoder not found for node %s - node may not be completely/correctly rendered\n", gf_node_get_class_name(node)));
	}
#ifndef GPAC_DISABLE_VRML
	if (gf_node_get_tag(node)==TAG_MPEG4_BitWrapper) {
		compositor_init_bitwrapper(compositor, node);
	}
#endif
}
