display_pids(struct writer *w, lldpctl_atom_t *port)
{
	lldpctl_atom_t *pids, *pid;
	pids = lldpctl_atom_get(port, lldpctl_k_port_pis);
	lldpctl_atom_foreach(pids, pid) {
		const char *pi = lldpctl_atom_get_str(pid, lldpctl_k_pi_id);
		if (pi && strlen(pi) > 0)
			tag_datatag(w, "pi", "PI", pi);
	}
	lldpctl_atom_dec_ref(pids);
}
