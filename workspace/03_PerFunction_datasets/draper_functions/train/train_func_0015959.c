snd_hdac_ext_stream_get_spbmaxfifo(struct hdac_ext_bus *ebus,
				 struct hdac_ext_stream *stream)
{
	struct hdac_bus *bus = &ebus->bus;

	if (!ebus->spbcap) {
		dev_err(bus->dev, "Address of SPB capability is NULL");
		return -EINVAL;
	}

	return readl(stream->fifo_addr);
}
