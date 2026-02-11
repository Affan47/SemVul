map_capability(struct pci_dev *dev, int off,
				    size_t minlen,
				    u32 align,
				    u32 start, u32 size,
				    size_t *len)
{
	u8 bar;
	u32 offset, length;
	void __iomem *p;

	pci_read_config_byte(dev, off + offsetof(struct virtio_pci_cap,
						 bar),
			     &bar);
	pci_read_config_dword(dev, off + offsetof(struct virtio_pci_cap, offset),
			     &offset);
	pci_read_config_dword(dev, off + offsetof(struct virtio_pci_cap, length),
			      &length);

	if (length <= start) {
		dev_err(&dev->dev,
			"virtio_pci: bad capability len %u (>%u expected)\n",
			length, start);
		return NULL;
	}

	if (length - start < minlen) {
		dev_err(&dev->dev,
			"virtio_pci: bad capability len %u (>=%zu expected)\n",
			length, minlen);
		return NULL;
	}

	length -= start;

	if (start + offset < offset) {
		dev_err(&dev->dev,
			"virtio_pci: map wrap-around %u+%u\n",
			start, offset);
		return NULL;
	}

	offset += start;

	if (offset & (align - 1)) {
		dev_err(&dev->dev,
			"virtio_pci: offset %u not aligned to %u\n",
			offset, align);
		return NULL;
	}

	if (length > size)
		length = size;

	if (len)
		*len = length;

	if (minlen + offset < minlen ||
	    minlen + offset > pci_resource_len(dev, bar)) {
		dev_err(&dev->dev,
			"virtio_pci: map virtio %zu@%u "
			"out of range on bar %i length %lu\n",
			minlen, offset,
			bar, (unsigned long)pci_resource_len(dev, bar));
		return NULL;
	}

	p = pci_iomap_range(dev, bar, offset, length);
	if (!p)
		dev_err(&dev->dev,
			"virtio_pci: unable to map virtio %u@%u on bar %i\n",
			length, offset, bar);
	return p;
}
