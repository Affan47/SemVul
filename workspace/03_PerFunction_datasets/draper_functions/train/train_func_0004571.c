load_shared(mem_cred_t *secrets, chunk_t line, int line_nr,
						shared_key_type_t type, chunk_t ids)
{
	shared_key_t *shared_key;
	linked_list_t *owners;
	chunk_t secret = chunk_empty;
	bool any = TRUE;

	err_t ugh = extract_secret(&secret, &line);
	if (ugh != NULL)
	{
		DBG1(DBG_CFG, "line %d: malformed secret: %s", line_nr, ugh);
		return FALSE;
	}
	shared_key = shared_key_create(type, secret);
	DBG1(DBG_CFG, "  loaded %N secret for %s", shared_key_type_names, type,
		 ids.len > 0 ? (char*)ids.ptr : "%any");
	DBG4(DBG_CFG, "  secret: %#B", &secret);

	owners = linked_list_create();
	while (ids.len > 0)
	{
		chunk_t id;
		identification_t *peer_id;

		ugh = extract_value(&id, &ids);
		if (ugh != NULL)
		{
			DBG1(DBG_CFG, "line %d: %s", line_nr, ugh);
			shared_key->destroy(shared_key);
			owners->destroy_offset(owners, offsetof(identification_t, destroy));
			return FALSE;
		}
		if (id.len == 0)
		{
			continue;
		}


		*(id.ptr + id.len) = '\0';
		peer_id = identification_create_from_string(id.ptr);
		if (peer_id->get_type(peer_id) == ID_ANY)
		{
			peer_id->destroy(peer_id);
			continue;
		}

		owners->insert_last(owners, peer_id);
		any = FALSE;
	}
	if (any)
	{
		owners->insert_last(owners,
					identification_create_from_encoding(ID_ANY, chunk_empty));
	}
	secrets->add_shared_list(secrets, shared_key, owners);
	return TRUE;
}
