xmms_xform_outdata_type_set (xmms_xform_t *xform, xmms_stream_type_t *type)
{
	xmms_object_ref (type);
	xform->out_type = type;
}
