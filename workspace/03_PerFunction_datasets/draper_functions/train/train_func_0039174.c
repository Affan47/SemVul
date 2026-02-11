divas_um_idi_create_entity(dword adapter_nr, void *file)
{
	divas_um_idi_entity_t *e;
	diva_um_idi_adapter_t *a;
	diva_os_spin_lock_magic_t old_irql;

	if ((e = (divas_um_idi_entity_t *) diva_os_malloc(0, sizeof(*e)))) {
		memset(e, 0x00, sizeof(*e));
		if (!
		    (e->os_context =
		     diva_os_malloc(0, diva_os_get_context_size()))) {
			DBG_LOG(("E(%08x) no memory for os context", e));
			diva_os_free(0, e);
			return NULL;
		}
		memset(e->os_context, 0x00, diva_os_get_context_size());

		if ((diva_data_q_init(&e->data, 2048 + 512, 16))) {
			diva_os_free(0, e->os_context);
			diva_os_free(0, e);
			return NULL;
		}
		if ((diva_data_q_init(&e->rc, sizeof(diva_um_idi_ind_hdr_t), 2))) {
			diva_data_q_finit(&e->data);
			diva_os_free(0, e->os_context);
			diva_os_free(0, e);
			return NULL;
		}

		diva_os_enter_spin_lock(&adapter_lock, &old_irql, "create_entity");


		if (!(a = diva_um_idi_find_adapter(adapter_nr))) {


			diva_os_leave_spin_lock(&adapter_lock, &old_irql, "create_entity");

			DBG_LOG(("A: no adapter(%ld)", adapter_nr));

			cleanup_entity(e);
			diva_os_free(0, e->os_context);
			diva_os_free(0, e);

			return NULL;
		}

		e->os_ref = file;
		e->adapter = a;

		list_add_tail(&e->link, &a->entity_q);

		diva_os_leave_spin_lock(&adapter_lock, &old_irql, "create_entity");

		DBG_LOG(("A(%ld), create E(%08x)", adapter_nr, e));
	}

	return (e);
}
