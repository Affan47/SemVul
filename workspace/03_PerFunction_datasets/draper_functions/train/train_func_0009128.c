lldpctl_atom_set_buffer(lldpctl_atom_t *atom, lldpctl_key_t key,
    const u_int8_t* value, size_t length)
{
	if (atom == NULL) return NULL;
	RESET_ERROR(atom->conn);

	if (atom->set_buffer == NULL) {
		SET_ERROR(atom->conn, LLDPCTL_ERR_NOT_EXIST);
		return NULL;
	}
	return atom->set_buffer(atom, key, value, length);
}
