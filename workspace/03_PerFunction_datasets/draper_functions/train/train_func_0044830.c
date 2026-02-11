_lldpctl_atom_get_str_vlan(lldpctl_atom_t *atom, lldpctl_key_t key)
{
	struct _lldpctl_atom_vlan_t *m =
	    (struct _lldpctl_atom_vlan_t *)atom;


	switch (key) {
	case lldpctl_k_vlan_name:
		return m->vlan->v_name;
	default:
		SET_ERROR(atom->conn, LLDPCTL_ERR_NOT_EXIST);
		return NULL;
	}
}
