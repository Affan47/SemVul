s2io_club_tcp_session(struct ring_info *ring_data, u8 *buffer,
				 u8 **tcp, u32 *tcp_len, struct lro **lro,
				 struct RxD_t *rxdp, struct s2io_nic *sp)
{
	struct iphdr *ip;
	struct tcphdr *tcph;
	int ret = 0, i;
	u16 vlan_tag = 0;
	struct swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	ret = check_L2_lro_capable(buffer, &ip, (struct tcphdr **)tcp,
				   rxdp, sp);
	if (ret)
		return ret;

	DBG_PRINT(INFO_DBG, "IP Saddr: %x Daddr: %x\n", ip->saddr, ip->daddr);

	vlan_tag = RXD_GET_VLAN_TAG(rxdp->Control_2);
	tcph = (struct tcphdr *)*tcp;
	*tcp_len = get_l4_pyld_length(ip, tcph);
	for (i = 0; i < MAX_LRO_SESSIONS; i++) {
		struct lro *l_lro = &ring_data->lro0_n[i];
		if (l_lro->in_use) {
			if (check_for_socket_match(l_lro, ip, tcph))
				continue;

			*lro = l_lro;

			if ((*lro)->tcp_next_seq != ntohl(tcph->seq)) {
				DBG_PRINT(INFO_DBG, "%s: Out of sequence. "
					  "expected 0x%x, actual 0x%x\n",
					  __func__,
					  (*lro)->tcp_next_seq,
					  ntohl(tcph->seq));

				swstats->outof_sequence_pkts++;
				ret = 2;
				break;
			}

			if (!verify_l3_l4_lro_capable(l_lro, ip, tcph,
						      *tcp_len))
				ret = 1;
			else
				ret = 2;
			break;
		}
	}

	if (ret == 0) {


		if (verify_l3_l4_lro_capable(NULL, ip, tcph, *tcp_len))
			return 5;

		for (i = 0; i < MAX_LRO_SESSIONS; i++) {
			struct lro *l_lro = &ring_data->lro0_n[i];
			if (!(l_lro->in_use)) {
				*lro = l_lro;
				ret = 3;
				break;
			}
		}
	}

	if (ret == 0) {
		DBG_PRINT(INFO_DBG, "%s: All LRO sessions already in use\n",
			  __func__);
		*lro = NULL;
		return ret;
	}

	switch (ret) {
	case 3:
		initiate_new_session(*lro, buffer, ip, tcph, *tcp_len,
				     vlan_tag);
		break;
	case 2:
		update_L3L4_header(sp, *lro);
		break;
	case 1:
		aggregate_new_rx(*lro, ip, tcph, *tcp_len);
		if ((*lro)->sg_num == sp->lro_max_aggr_per_sess) {
			update_L3L4_header(sp, *lro);
			ret = 4;
		}
		break;
	default:
		DBG_PRINT(ERR_DBG, "%s: Don't know, can't say!!\n", __func__);
		break;
	}

	return ret;
}
