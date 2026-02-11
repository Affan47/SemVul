ath_node_create_tgt(void *Context, A_UINT16 Command,
				A_UINT16 SeqNo, A_UINT8 *data, a_int32_t datalen)
{
	struct ath_softc_tgt *sc = (struct ath_softc_tgt *)Context;
	struct ieee80211_node_target *node;
	a_uint8_t vap_index;
	a_uint8_t node_index;

	node = (struct ieee80211_node_target *)data;

	node_index = node->ni_nodeindex;

	node->ni_htcap = adf_os_ntohs(node->ni_htcap);
	node->ni_flags = adf_os_ntohs(node->ni_flags);
	node->ni_maxampdu = adf_os_ntohs(node->ni_maxampdu);

	adf_os_mem_copy(&(sc->sc_sta[node_index].ni), node,
			NODE_TARGET_SIZE);

    	vap_index = sc->sc_sta[node_index].ni.ni_vapindex;
	sc->sc_sta[node_index].ni.ni_vap = &(sc->sc_vap[vap_index].av_vap);
	if(sc->sc_sta[node_index].ni.ni_is_vapnode == 1)
		sc->sc_vap[vap_index].av_vap.iv_nodeindex = node_index;

	sc->sc_sta[node_index].an_valid = 1;
	sc->sc_sta[node_index].ni.ni_txseqmgmt = 0;
	sc->sc_sta[node_index].ni.ni_iv16 = 0;
	sc->sc_sta[node_index].ni.ni_iv32 = 0;

	owl_tgt_node_init(&sc->sc_sta[node_index]);

	wmi_cmd_rsp(sc->tgt_wmi_handle, Command, SeqNo, NULL, 0);
}
