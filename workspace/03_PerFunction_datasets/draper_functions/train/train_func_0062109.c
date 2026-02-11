vc4_crtc_irq_handler(int irq, void *data)
{
	struct vc4_crtc *vc4_crtc = data;
	u32 stat = CRTC_READ(PV_INTSTAT);
	irqreturn_t ret = IRQ_NONE;

	if (stat & PV_INT_VFP_START) {
		CRTC_WRITE(PV_INTSTAT, PV_INT_VFP_START);
		drm_crtc_handle_vblank(&vc4_crtc->base);
		vc4_crtc_handle_page_flip(vc4_crtc);
		ret = IRQ_HANDLED;
	}

	return ret;
}
