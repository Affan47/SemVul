_lldpctl_atom_new_med_power(lldpctl_atom_t *atom, va_list ap)
{
	struct _lldpctl_atom_med_power_t *mpow =
	    (struct _lldpctl_atom_med_power_t *)atom;
	mpow->parent = va_arg(ap, struct _lldpctl_atom_port_t *);
	lldpctl_atom_inc_ref((lldpctl_atom_t *)mpow->parent);
	return 1;
}
