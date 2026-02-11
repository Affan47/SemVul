multi_send_object(object *objp)
{
	if (cannot_send_data()) {
		return;
	}

	multi_sexp_ensure_space_remains(sizeof(ushort));


	type[packet_size] = TYPE_OBJECT;

	ADD_USHORT(objp->net_signature);
	current_argument_count += sizeof(ushort);
}
