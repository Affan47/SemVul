ipath_write_umem32(struct ipath_devdata *dd, void __iomem *caddr,
			      const void __user *uaddr, size_t count)
{
	u32 __iomem *reg_addr = caddr;
	const u32 __iomem *reg_end = reg_addr + (count / sizeof(u32));
	int ret;

	if (reg_addr < (u32 __iomem *) dd->ipath_kregbase ||
	    reg_end > (u32 __iomem *) dd->ipath_kregend) {
		ret = -EINVAL;
		goto bail;
	}
	while (reg_addr < reg_end) {
		u32 data;
		if (copy_from_user(&data, uaddr, sizeof(data))) {
			ret = -EFAULT;
			goto bail;
		}
		writel(data, reg_addr);

		reg_addr++;
		uaddr += sizeof(u32);
	}
	ret = 0;
bail:
	return ret;
}
