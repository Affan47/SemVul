gr_dbgprint_devreq(struct gr_udc *dev, u8 type, u8 request,
			       u16 value, u16 index, u16 length)
{
	dev_vdbg(dev->dev, "REQ: %02x.%02x v%04x i%04x l%04x\n",
		 type, request, value, index, length);
}
