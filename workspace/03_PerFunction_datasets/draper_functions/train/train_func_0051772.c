brcmf_sdiod_change_state(struct brcmf_sdio_dev *sdiodev,
			      enum brcmf_sdiod_state state)
{
	if (sdiodev->state == BRCMF_SDIOD_NOMEDIUM ||
	    state == sdiodev->state)
		return;

	brcmf_dbg(TRACE, "%d -> %d\n", sdiodev->state, state);
	switch (sdiodev->state) {
	case BRCMF_SDIOD_DATA:

		brcmf_bus_change_state(sdiodev->bus_if, BRCMF_BUS_DOWN);
		break;
	case BRCMF_SDIOD_DOWN:

		if (state == BRCMF_SDIOD_DATA)
			brcmf_bus_change_state(sdiodev->bus_if, BRCMF_BUS_UP);
		break;
	default:
		break;
	}
	sdiodev->state = state;
}
