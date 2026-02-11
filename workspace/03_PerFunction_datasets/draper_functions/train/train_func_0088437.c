run_callback_cb (BatchOperation *op)
{
	if (op->callback != NULL)
		op->callback (op->id, op->type, op->entry, op->error, op->user_data);


	op->callback = NULL;

	return FALSE;
}
