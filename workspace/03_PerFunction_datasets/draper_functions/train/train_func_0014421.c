vmw_view_id_ok(u32 user_key, enum vmw_view_type view_type)
{
	return (user_key < SVGA_COTABLE_MAX_IDS &&
		view_type < vmw_view_max);
}
