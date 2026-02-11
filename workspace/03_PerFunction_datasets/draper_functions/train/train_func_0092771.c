bfa_flash_write_send(struct bfa_flash *flash)
{
	struct bfi_flash_write_req *msg =
			(struct bfi_flash_write_req *) flash->mb.msg;
	u32	len;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	msg->offset = be32_to_cpu(flash->addr_off + flash->offset);
	len = (flash->residue < BFA_FLASH_DMA_BUF_SZ) ?
	       flash->residue : BFA_FLASH_DMA_BUF_SZ;
	msg->length = be32_to_cpu(len);


	msg->last = (len == flash->residue) ? 1 : 0;

	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_WRITE_REQ,
		    bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, len, flash->dbuf_pa);
	memcpy(flash->dbuf_kva, flash->ubuf + flash->offset, len);
	bfa_nw_ioc_mbox_queue(flash->ioc, &flash->mb, NULL, NULL);

	flash->residue -= len;
	flash->offset += len;
}
