gf_term_on_node_modified(void *_is, GF_Node *node)
{
	GF_Scene *scene = (GF_Scene *)_is;
	if (!scene) return;
	if (!node) {
		gf_sc_invalidate(scene->root_od->term->compositor, NULL);
		return;
	}

	switch (gf_node_get_tag(node)) {
#ifndef GPAC_DISABLE_VRML
	case TAG_MPEG4_Inline:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Inline:
#endif
		gf_inline_on_modified(node);
		break;
	case TAG_MPEG4_MediaBuffer:
		break;
	case TAG_MPEG4_MediaControl:
		MC_Modified(node);
		break;
	case TAG_MPEG4_MediaSensor:
		MS_Modified(node);
		break;
	case TAG_MPEG4_InputSensor:
		InputSensorModified(node);
		break;
	case TAG_MPEG4_Conditional:
		break;
	case TAG_MPEG4_Storage:
		break;
#endif
	default: gf_sc_invalidate(scene->root_od->term->compositor, node); break;
	}
}
