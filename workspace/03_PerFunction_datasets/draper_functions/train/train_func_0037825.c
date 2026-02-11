IndexedCurve2D_GetNode(GF_Node *node, IndexedCurve2D *ic2d)
{
	GF_FieldInfo field;
	memset(ic2d, 0, sizeof(IndexedCurve2D));

	ic2d->sgprivate = node->sgprivate;

	if (gf_node_get_field(node, 0, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_SFNODE) return 0;
	ic2d->point = * (GF_Node **) field.far_ptr;

	if (gf_node_get_field(node, 1, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_SFFLOAT) return 0;
	ic2d->fineness = *(SFFloat *) field.far_ptr;

	if (gf_node_get_field(node, 2, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_MFINT32) return 0;
	ic2d->type = *(MFInt32 *) field.far_ptr;

	if (gf_node_get_field(node, 3, &field) != GF_OK) return 0;
	if (field.fieldType != GF_SG_VRML_MFINT32) return 0;
	ic2d->index = *(MFInt32 *) field.far_ptr;

	return 1;
}
