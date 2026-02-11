snd_hdac_bus_free_stream_pages(struct hdac_bus *bus)
{
	struct hdac_stream *s;

	list_for_each_entry(s, &bus->stream_list, list) {
		if (s->bdl.area)
			bus->io_ops->dma_free_pages(bus, &s->bdl);
	}

	if (bus->rb.area)
		bus->io_ops->dma_free_pages(bus, &bus->rb);
	if (bus->posbuf.area)
		bus->io_ops->dma_free_pages(bus, &bus->posbuf);
}
