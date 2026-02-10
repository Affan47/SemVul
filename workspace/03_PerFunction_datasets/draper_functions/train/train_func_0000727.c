erase_xfer(partition_t *part,
		      uint16_t xfernum)
{
    int ret;
    struct xfer_info_t *xfer;
    struct erase_info *erase;

    xfer = &part->XferInfo[xfernum];
    pr_debug("ftl_cs: erasing xfer unit at 0x%x\n", xfer->Offset);
    xfer->state = XFER_ERASING;


    erase=kmalloc(sizeof(struct erase_info), GFP_KERNEL);
    if (!erase)
            return -ENOMEM;

    erase->mtd = part->mbd.mtd;
    erase->callback = ftl_erase_callback;
    erase->addr = xfer->Offset;
    erase->len = 1 << part->header.EraseUnitSize;
    erase->priv = (u_long)part;

    ret = mtd_erase(part->mbd.mtd, erase);

    if (!ret)
	    xfer->EraseCount++;
    else
	    kfree(erase);

    return ret;
}
