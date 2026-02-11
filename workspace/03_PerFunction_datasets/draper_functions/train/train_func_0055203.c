delete_ups(upstype_t *target)
{
	upstype_t	*ptr, *last;

	if (!target)
		return;

	ptr = last = firstups;

	while (ptr) {
		if (ptr == target) {
			upslogx(LOG_NOTICE, "Deleting UPS [%s]", target->name);


			kick_login_clients(target->name);


			if (ptr == last)
				firstups = ptr->next;
			else
				last->next = ptr->next;

			if (ptr->sock_fd != -1)
				close(ptr->sock_fd);


			sstate_infofree(ptr);
			sstate_cmdfree(ptr);
			pconf_finish(&ptr->sock_ctx);

			free(ptr->fn);
			free(ptr->name);
			free(ptr->desc);
			free(ptr);

			return;
		}

		last = ptr;
		ptr = ptr->next;
	}


	upslogx(LOG_ERR, "delete_ups: UPS not found");
}
