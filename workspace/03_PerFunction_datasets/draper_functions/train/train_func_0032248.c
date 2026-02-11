ensure_data_in_currentcb(struct read_request *request)
{
    local_cache_buffer_t *lb = request->node->lcb;
    cbindex_t *nearest;

    nearest = find_closest_existing_cb( request->bnum, lb->currentcb);

    if( nearest->bnum == request->bnum ) {
	update_currentcb_to_existing_cb(request, nearest);
    } else {
	update_currentcb_by_reading(request, nearest);
    }

    record_read_hit(lb, lb->currentcb);
}
