hwi_free_async_msg(struct beiscsi_hba *phba,
			       struct hwi_async_pdu_context *pasync_ctx,
			       unsigned int cri)
{
	struct async_pdu_handle *pasync_handle, *tmp_handle;
	struct list_head *plist;

	plist  = &pasync_ctx->async_entry[cri].wait_queue.list;
	list_for_each_entry_safe(pasync_handle, tmp_handle, plist, link) {
		list_del(&pasync_handle->link);

		if (pasync_handle->is_header) {
			list_add_tail(&pasync_handle->link,
				      &pasync_ctx->async_header.free_list);
			pasync_ctx->async_header.free_entries++;
		} else {
			list_add_tail(&pasync_handle->link,
				      &pasync_ctx->async_data.free_list);
			pasync_ctx->async_data.free_entries++;
		}
	}

	INIT_LIST_HEAD(&pasync_ctx->async_entry[cri].wait_queue.list);
	pasync_ctx->async_entry[cri].wait_queue.hdr_received = 0;
	pasync_ctx->async_entry[cri].wait_queue.bytes_received = 0;
}
