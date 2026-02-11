ath_rc_mask_tgt(void *Context, A_UINT16 Command,
			    A_UINT16 SeqNo, A_UINT8 *buffer, a_int32_t Length)
{
	struct ath_softc_tgt *sc = (struct ath_softc_tgt *)Context;
	struct wmi_rc_rate_mask_cmd *wmi_data = (struct wmi_rc_rate_mask_cmd *)buffer;
	int idx, band, i;

	idx = wmi_data->vap_index;
	band = wmi_data->band;

	sc->sc_vap[idx].av_rate_mask[band] = adf_os_ntohl(wmi_data->mask);

	if (sc->sc_vap[idx].av_rate_mask[band]) {
		for (i = 0; i < RATE_TABLE_SIZE; i++) {
			if ((1 << i) & sc->sc_vap[idx].av_rate_mask[band]) {
				sc->sc_vap[idx].av_minrateidx[band] = i;
				break;
			}
		}
	} else {
		sc->sc_vap[idx].av_minrateidx[band] = 0;
	}

	wmi_cmd_rsp(sc->tgt_wmi_handle, Command, SeqNo, NULL, 0);
}
