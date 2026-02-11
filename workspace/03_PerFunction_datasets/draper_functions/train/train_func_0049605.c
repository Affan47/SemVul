mmio_pipe_open(struct trace_iterator *iter)
{
	struct header_iter *hiter;
	struct trace_seq *s = &iter->seq;

	trace_seq_puts(s, "VERSION 20070824\n");

	hiter = kzalloc(sizeof(*hiter), GFP_KERNEL);
	if (!hiter)
		return;

	hiter->dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
	iter->private = hiter;
}
