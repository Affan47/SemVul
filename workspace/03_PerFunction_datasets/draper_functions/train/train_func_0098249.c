set_all_nodma_rtail(struct hfi1_devdata *dd)
{
	int i;

	for (i = 0; i < dd->first_user_ctxt; i++)
		dd->rcd[i]->do_interrupt =
			&handle_receive_interrupt_nodma_rtail;
}
