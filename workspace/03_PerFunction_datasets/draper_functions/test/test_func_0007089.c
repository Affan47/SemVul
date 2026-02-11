efx_mcdi_release(struct efx_mcdi_iface *mcdi)
{
	if (mcdi->mode == MCDI_MODE_EVENTS) {
		struct efx_mcdi_async_param *async;
		struct efx_nic *efx = mcdi->efx;


		spin_lock_bh(&mcdi->async_lock);
		async = list_first_entry_or_null(
			&mcdi->async_list, struct efx_mcdi_async_param, list);
		if (async) {
			mcdi->state = MCDI_STATE_RUNNING_ASYNC;
			efx_mcdi_send_request(efx, async->cmd,
					      (const efx_dword_t *)(async + 1),
					      async->inlen);
			mod_timer(&mcdi->async_timer,
				  jiffies + MCDI_RPC_TIMEOUT);
		}
		spin_unlock_bh(&mcdi->async_lock);

		if (async)
			return;
	}

	mcdi->state = MCDI_STATE_QUIESCENT;
	wake_up(&mcdi->wq);
}
