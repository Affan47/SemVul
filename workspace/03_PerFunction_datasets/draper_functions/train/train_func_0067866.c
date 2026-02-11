fotg210_is_epnstall(struct fotg210_ep *ep)
{
	struct fotg210_udc *fotg210 = ep->fotg210;
	u32 value;
	void __iomem *reg;

	reg = (ep->dir_in) ?
		fotg210->reg + FOTG210_INEPMPSR(ep->epnum) :
		fotg210->reg + FOTG210_OUTEPMPSR(ep->epnum);
	value = ioread32(reg);
	return value & INOUTEPMPSR_STL_EP ? 1 : 0;
}
