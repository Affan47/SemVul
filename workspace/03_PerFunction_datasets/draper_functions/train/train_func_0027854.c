brcmf_fws_hanger_mark_suppressed(struct brcmf_fws_hanger *h,
					    u32 slot_id)
{
	if (slot_id >= BRCMF_FWS_HANGER_MAXITEMS)
		return -ENOENT;

	if (h->items[slot_id].state == BRCMF_FWS_HANGER_ITEM_STATE_FREE) {
		brcmf_err("entry not in use\n");
		return -EINVAL;
	}

	h->items[slot_id].state = BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED;
	return 0;
}
