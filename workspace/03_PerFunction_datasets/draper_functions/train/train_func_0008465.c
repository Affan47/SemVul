object_ego_is_visible(const object_type *o_ptr)
{
	if (!o_ptr->ego)
		return FALSE;

	if (o_ptr->tval == TV_LIGHT)
		return TRUE;

	if ((o_ptr->ident & IDENT_NAME) || (o_ptr->ident & IDENT_STORE))
		return TRUE;
	else
		return FALSE;
}
