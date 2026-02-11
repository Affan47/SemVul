pk_backend_is_implemented (PkBackend *backend, PkRoleEnum role)
{
	PkBitfield roles;
	g_return_val_if_fail (PK_IS_BACKEND (backend), FALSE);
	roles = pk_backend_get_roles (backend);
	return pk_bitfield_contain (roles, role);
}
