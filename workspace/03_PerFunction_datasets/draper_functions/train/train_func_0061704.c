nvm_factory_blks(struct ppa_addr ppa, int nr_blks, u8 *blks,
								void *private)
{
	struct factory_blks *f = private;
	struct nvm_dev *dev = f->dev;
	int i, lunoff;

	lunoff = factory_blk_offset(dev, ppa.g.ch, ppa.g.lun);


	for (i = 0; i < nr_blks; i++) {
		switch (blks[i]) {
		case NVM_BLK_T_FREE:
			if (f->flags & NVM_FACTORY_ERASE_ONLY_USER)
				set_bit(i, &f->blks[lunoff]);
			break;
		case NVM_BLK_T_HOST:
			if (!(f->flags & NVM_FACTORY_RESET_HOST_BLKS))
				set_bit(i, &f->blks[lunoff]);
			break;
		case NVM_BLK_T_GRWN_BAD:
			if (!(f->flags & NVM_FACTORY_RESET_GRWN_BBLKS))
				set_bit(i, &f->blks[lunoff]);
			break;
		default:
			set_bit(i, &f->blks[lunoff]);
			break;
		}
	}

	return 0;
}
