write_adapter_mem(struct c4iw_rdev *rdev, u32 addr, u32 len,
			     void *data)
{
	if (is_t5(rdev->lldi.adapter_type) && use_dsgl) {
		if (len > inline_threshold) {
			if (_c4iw_write_mem_dma(rdev, addr, len, data)) {
				printk_ratelimited(KERN_WARNING
						   "%s: dma map"
						   " failure (non fatal)\n",
						   pci_name(rdev->lldi.pdev));
				return _c4iw_write_mem_inline(rdev, addr, len,
							      data);
			} else
				return 0;
		} else
			return _c4iw_write_mem_inline(rdev, addr, len, data);
	} else
		return _c4iw_write_mem_inline(rdev, addr, len, data);
}
