build_vault_type(struct cave*c, int y0, int x0, int typ, const char *label)
{
	vault_type *v_ptr = random_vault(typ);
	if (v_ptr == NULL) {

		return FALSE;
	}

	ROOM_LOG("%s (%s)", label, v_ptr->name);


	c->mon_rating += v_ptr->rat;


	build_vault(c, y0, x0, v_ptr->hgt, v_ptr->wid, v_ptr->text);

	return TRUE;
}
