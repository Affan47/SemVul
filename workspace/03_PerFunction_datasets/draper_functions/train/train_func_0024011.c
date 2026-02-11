gkd_ssh_agent_proto_write_mpi_v1 (EggBuffer *resp,
                                  const GckAttribute *attr)
{
	guchar *data;

	g_return_val_if_fail (attr->length * 8 < G_MAXUSHORT, FALSE);

	if (!egg_buffer_add_uint16 (resp, attr->length * 8))
		return FALSE;

	data = egg_buffer_add_empty (resp, attr->length);
	if (data == NULL)
		return FALSE;
	memcpy (data, attr->value, attr->length);
	return TRUE;
}
