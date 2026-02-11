diva_user_mode_idi_create_adapter(const DESCRIPTOR *d, int adapter_nr)
{
	diva_os_spin_lock_magic_t old_irql;
	diva_um_idi_adapter_t *a =
		(diva_um_idi_adapter_t *) diva_os_malloc(0,
							 sizeof
							 (diva_um_idi_adapter_t));

	if (!a) {
		return (-1);
	}
	memset(a, 0x00, sizeof(*a));
	INIT_LIST_HEAD(&a->entity_q);

	a->d = *d;
	a->adapter_nr = adapter_nr;

	DBG_LOG(("DIDD_ADD A(%d), type:%02x, features:%04x, channels:%d",
		 adapter_nr, a->d.type, a->d.features, a->d.channels));

	diva_os_enter_spin_lock(&adapter_lock, &old_irql, "create_adapter");
	list_add_tail(&a->link, &adapter_q);
	diva_os_leave_spin_lock(&adapter_lock, &old_irql, "create_adapter");
	return (0);
}
