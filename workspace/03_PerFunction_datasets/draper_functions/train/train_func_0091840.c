ompi_seq_tracker_check_duplicate(
    ompi_seq_tracker_t* seq_tracker,
    uint32_t seq_id)
{
    ompi_seq_tracker_range_t* item;
    const ompi_seq_tracker_range_t* sentinel = (ompi_seq_tracker_range_t*)opal_list_get_end(&seq_tracker->seq_ids);
    int8_t direction = 0;

    item = seq_tracker->seq_ids_current;
    while(true) {
        if(sentinel == item) {
            return false;
        } else if(item->seq_id_high >= seq_id && item->seq_id_low <= seq_id) {
            seq_tracker->seq_ids_current = (ompi_seq_tracker_range_t*) item;
            return true;
        } else if(seq_id > item->seq_id_high && direction != -1) {
            direction = 1;
            item = (ompi_seq_tracker_range_t*) opal_list_get_next(item);
        } else if(seq_id < item->seq_id_low && direction != 1) {
            direction = -1;
            item = (ompi_seq_tracker_range_t*) opal_list_get_prev(item);
        } else {
            return false;
        }
    }
}
