_pack_local_resv(local_resv_t *object,
			     uint16_t rpc_version, Buf buffer)
{
	packstr(object->assocs, buffer);
	packstr(object->cpus, buffer);
	packstr(object->flags, buffer);
	packstr(object->id, buffer);
	packstr(object->name, buffer);
	packstr(object->nodes, buffer);
	packstr(object->node_inx, buffer);
	packstr(object->time_end, buffer);
	packstr(object->time_start, buffer);
}
