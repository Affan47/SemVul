periodic_unlink(struct fotg210_hcd *fotg210, unsigned frame,
		void *ptr)
{
	union fotg210_shadow *prev_p = &fotg210->pshadow[frame];
	__hc32 *hw_p = &fotg210->periodic[frame];
	union fotg210_shadow here = *prev_p;


	while (here.ptr && here.ptr != ptr) {
		prev_p = periodic_next_shadow(fotg210, prev_p,
				Q_NEXT_TYPE(fotg210, *hw_p));
		hw_p = shadow_next_periodic(fotg210, &here,
				Q_NEXT_TYPE(fotg210, *hw_p));
		here = *prev_p;
	}

	if (!here.ptr)
		return;


	*prev_p = *periodic_next_shadow(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));

	*hw_p = *shadow_next_periodic(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));
}
