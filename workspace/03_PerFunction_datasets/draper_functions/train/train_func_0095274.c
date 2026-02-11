brcmf_commonring_write_available(struct brcmf_commonring *commonring)
{
	u16 available;
	bool retry = true;

again:
	if (commonring->r_ptr <= commonring->w_ptr)
		available = commonring->depth - commonring->w_ptr +
			    commonring->r_ptr;
	else
		available = commonring->r_ptr - commonring->w_ptr;

	if (available > 1) {
		if (!commonring->was_full)
			return true;
		if (available > commonring->depth / 8) {
			commonring->was_full = false;
			return true;
		}
		if (retry) {
			if (commonring->cr_update_rptr)
				commonring->cr_update_rptr(commonring->cr_ctx);
			retry = false;
			goto again;
		}
		return false;
	}

	if (retry) {
		if (commonring->cr_update_rptr)
			commonring->cr_update_rptr(commonring->cr_ctx);
		retry = false;
		goto again;
	}

	commonring->was_full = true;
	return false;
}
