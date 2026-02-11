fifo_cell_out(struct snd_seq_fifo *f)
{
	struct snd_seq_event_cell *cell;

	if ((cell = f->head) != NULL) {
		f->head = cell->next;


		if (f->tail == cell)
			f->tail = NULL;

		cell->next = NULL;
		f->cells--;
	}

	return cell;
}
