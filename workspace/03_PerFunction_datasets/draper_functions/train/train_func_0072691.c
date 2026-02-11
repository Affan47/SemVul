sdio_read_cis(struct mmc_card *card, struct sdio_func *func)
{
	int ret;
	struct sdio_func_tuple *this, **prev;
	unsigned i, ptr = 0;


	for (i = 0; i < 3; i++) {
		unsigned char x, fn;

		if (func)
			fn = func->num;
		else
			fn = 0;

		ret = mmc_io_rw_direct(card, 0, 0,
			SDIO_FBR_BASE(fn) + SDIO_FBR_CIS + i, 0, &x);
		if (ret)
			return ret;
		ptr |= x << (i * 8);
	}

	if (func)
		prev = &func->tuples;
	else
		prev = &card->tuples;

	BUG_ON(*prev);

	do {
		unsigned char tpl_code, tpl_link;

		ret = mmc_io_rw_direct(card, 0, 0, ptr++, 0, &tpl_code);
		if (ret)
			break;


		if (tpl_code == 0xff)
			break;


		if (tpl_code == 0x00)
			continue;

		ret = mmc_io_rw_direct(card, 0, 0, ptr++, 0, &tpl_link);
		if (ret)
			break;


		if (tpl_link == 0xff)
			break;

		this = kmalloc(sizeof(*this) + tpl_link, GFP_KERNEL);
		if (!this)
			return -ENOMEM;

		for (i = 0; i < tpl_link; i++) {
			ret = mmc_io_rw_direct(card, 0, 0,
					       ptr + i, 0, &this->data[i]);
			if (ret)
				break;
		}
		if (ret) {
			kfree(this);
			break;
		}


		ret = cis_tpl_parse(card, func, "CIS",
				    cis_tpl_list, ARRAY_SIZE(cis_tpl_list),
				    tpl_code, this->data, tpl_link);
		if (ret == -EILSEQ || ret == -ENOENT) {


			this->next = NULL;
			this->code = tpl_code;
			this->size = tpl_link;
			*prev = this;
			prev = &this->next;

			if (ret == -ENOENT) {

				pr_warn_ratelimited("%s: queuing unknown"
				       " CIS tuple 0x%02x (%u bytes)\n",
				       mmc_hostname(card->host),
				       tpl_code, tpl_link);
			}


			ret = 0;
		} else {


			kfree(this);
		}

		ptr += tpl_link;
	} while (!ret);


	if (func)
		*prev = card->tuples;

	return ret;
}
