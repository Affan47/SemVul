OffscreenGroup_GetNode(GF_Node *node, OffscreenGroup *og)
{
	GF_FieldInfo field;
	memset(og, 0, sizeof(OffscreenGroup));
	og->sgprivate = node->sgprivate;

	if (gf_node_get_field(node, 0, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_MFNODE) return 0;
	og->children = *(GF_ChildNodeItem **) field.far_ptr;

	if (gf_node_get_field(node, 1, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_SFINT32) return 0;
	og->offscreen = * (SFInt32 *) field.far_ptr;

	if (gf_node_get_field(node, 2, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_SFFLOAT) return 0;
	og->opacity = * (SFFloat *) field.far_ptr;
	return 1;
}
