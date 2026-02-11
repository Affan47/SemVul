_lldpctl_atom_set_str_med_power(lldpctl_atom_t *atom, lldpctl_key_t key,
    const char *value)
{
	switch (key) {
	case lldpctl_k_med_power_type:
		return _lldpctl_atom_set_int_med_power(atom, key,
		    map_reverse_lookup(port_med_pow_devicetype_map, value));
	case lldpctl_k_med_power_source:
		return _lldpctl_atom_set_int_med_power(atom, key,
		    map_reverse_lookup(port_med_pow_source_map2, value));
	case lldpctl_k_med_power_priority:
		return _lldpctl_atom_set_int_med_power(atom, key,
		    map_reverse_lookup(port_med_pow_priority_map.map, value));
	default:
		SET_ERROR(atom->conn, LLDPCTL_ERR_NOT_EXIST);
		return NULL;
	}
}
