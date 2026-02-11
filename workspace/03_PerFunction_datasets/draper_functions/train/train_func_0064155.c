plP_init(void)
{
    plsc->page_status = AT_EOP;

    (*plsc->dispatch_table->pl_init) ((struct PLStream_struct *) plsc);

    if (plsc->plbuf_write)
	plbuf_init(plsc);
}
