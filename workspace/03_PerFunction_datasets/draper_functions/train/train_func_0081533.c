csio_lnode_lookup_by_wwpn(struct csio_hw *hw, uint8_t *wwpn)
{
	struct list_head *tmp1, *tmp2;
	struct csio_lnode *sln = NULL, *cln = NULL;

	if (list_empty(&hw->sln_head)) {
		CSIO_INC_STATS(hw, n_lnlkup_miss);
		return NULL;
	}

	list_for_each(tmp1, &hw->sln_head) {
		sln = (struct csio_lnode *) tmp1;


		if (!memcmp(csio_ln_wwpn(sln), wwpn, 8))
			return sln;

		if (list_empty(&sln->cln_head))
			continue;


		list_for_each(tmp2, &sln->cln_head) {
			cln = (struct csio_lnode *) tmp2;

			if (!memcmp(csio_ln_wwpn(cln), wwpn, 8))
				return cln;
		}
	}
	return NULL;
}
