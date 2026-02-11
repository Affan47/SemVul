_destroy_filetxt_step_rec(void *object)
{
	filetxt_step_rec_t *step = (filetxt_step_rec_t *)object;
	if (step) {
		_free_filetxt_header(&step->header);
		xfree(step->stepname);
		xfree(step->nodes);
		xfree(step->account);
		xfree(step);
	}
}
