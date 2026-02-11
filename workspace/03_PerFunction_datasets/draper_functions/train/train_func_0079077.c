write_fifo(struct net2280_ep *ep, struct usb_request *req)
{
	struct net2280_ep_regs	__iomem *regs = ep->regs;
	u8			*buf;
	u32			tmp;
	unsigned		count, total;


	if (req) {
		buf = req->buf + req->actual;
		prefetch(buf);
		total = req->length - req->actual;
	} else {
		total = 0;
		buf = NULL;
	}


	count = ep->ep.maxpacket;
	if (count > total)
		count = total;

	ep_vdbg(ep->dev, "write %s fifo (IN) %d bytes%s req %p\n",
			ep->ep.name, count,
			(count != ep->ep.maxpacket) ? " (short)" : "",
			req);
	while (count >= 4) {


		tmp = get_unaligned((u32 *)buf);
		cpu_to_le32s(&tmp);
		writel(tmp, &regs->ep_data);
		buf += 4;
		count -= 4;
	}


	if (count || total < ep->ep.maxpacket) {
		tmp = count ? get_unaligned((u32 *)buf) : count;
		cpu_to_le32s(&tmp);
		set_fifo_bytecount(ep, count & 0x03);
		writel(tmp, &regs->ep_data);
	}


}
