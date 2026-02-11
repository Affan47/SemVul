ath9k_postprocess_radar_event(struct ath_softc *sc,
			      struct ath_radar_data *ard,
			      struct pulse_event *pe)
{
	u8 rssi;
	u16 dur;


	ard->pulse_bw_info &= 0x03;

	switch (ard->pulse_bw_info) {
	case PRI_CH_RADAR_FOUND:

		dur = ard->pulse_length_pri;
		DFS_STAT_INC(sc, pri_phy_errors);


		rssi = (ard->ext_rssi >= (ard->rssi + 3)) ? 0 : ard->rssi;
		break;
	case EXT_CH_RADAR_FOUND:

		dur = ard->pulse_length_ext;
		DFS_STAT_INC(sc, ext_phy_errors);


		rssi = (ard->rssi >= (ard->ext_rssi + 12)) ? 0 : ard->ext_rssi;
		break;
	case (PRI_CH_RADAR_FOUND | EXT_CH_RADAR_FOUND):


		if (ard->pulse_length_ext >= ard->pulse_length_pri)
			dur = ard->pulse_length_ext;
		else
			dur = ard->pulse_length_pri;
		DFS_STAT_INC(sc, dc_phy_errors);


		rssi = (ard->rssi < ard->ext_rssi) ? ard->ext_rssi : ard->rssi;
		break;
	default:


		DFS_STAT_INC(sc, bwinfo_discards);
		return false;
	}

	if (rssi == 0) {
		DFS_STAT_INC(sc, rssi_discards);
		return false;
	}


	pe->width = dur_to_usecs(sc->sc_ah, dur);
	pe->rssi = rssi;

	DFS_STAT_INC(sc, pulses_detected);
	return true;
}
