uwb_drp_ie_alloc(void)
{
	struct uwb_ie_drp *drp_ie;

	drp_ie = kzalloc(sizeof(struct uwb_ie_drp) +
			UWB_NUM_ZONES * sizeof(struct uwb_drp_alloc),
			GFP_KERNEL);
	if (drp_ie) {
		drp_ie->hdr.element_id = UWB_IE_DRP;
	}
	return drp_ie;
}
