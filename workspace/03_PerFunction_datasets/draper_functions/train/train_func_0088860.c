diva_data_q_ack_segment4read(diva_um_idi_data_queue_t *q)
{
	if (q->count) {
		q->length[q->read] = 0;
		q->count--;
		q->read++;
		if (q->read >= q->segments) {
			q->read = 0;
		}
	}
}
