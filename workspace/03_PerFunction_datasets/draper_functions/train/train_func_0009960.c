_lldpctl_atom_get_int_med_caelement(lldpctl_atom_t *atom, lldpctl_key_t key)
{
	struct _lldpctl_atom_med_caelement_t *m =
	    (struct _lldpctl_atom_med_caelement_t *)atom;

	switch (key) {
	case lldpctl_k_med_civicaddress_type:
		return m->type;
	default:
		return SET_ERROR(atom->conn, LLDPCTL_ERR_NOT_EXIST);
	}
}
