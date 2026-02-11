make_tx_data_wr(struct cxgbi_sock *csk, struct sk_buff *skb,
				   int dlen, int len, u32 credits, int compl)
{
	struct fw_ofld_tx_data_wr *req;
	unsigned int submode = cxgbi_skcb_ulp_mode(skb) & 3;
	unsigned int wr_ulp_mode = 0, val;
	bool imm = is_ofld_imm(skb);

	req = (struct fw_ofld_tx_data_wr *)__skb_push(skb, sizeof(*req));

	if (imm) {
		req->op_to_immdlen = htonl(FW_WR_OP_V(FW_OFLD_TX_DATA_WR) |
					FW_WR_COMPL_F |
					FW_WR_IMMDLEN_V(dlen));
		req->flowid_len16 = htonl(FW_WR_FLOWID_V(csk->tid) |
						FW_WR_LEN16_V(credits));
	} else {
		req->op_to_immdlen =
			cpu_to_be32(FW_WR_OP_V(FW_OFLD_TX_DATA_WR) |
					FW_WR_COMPL_F |
					FW_WR_IMMDLEN_V(0));
		req->flowid_len16 =
			cpu_to_be32(FW_WR_FLOWID_V(csk->tid) |
					FW_WR_LEN16_V(credits));
	}
	if (submode)
		wr_ulp_mode = FW_OFLD_TX_DATA_WR_ULPMODE_V(ULP2_MODE_ISCSI) |
				FW_OFLD_TX_DATA_WR_ULPSUBMODE_V(submode);
	val = skb_peek(&csk->write_queue) ? 0 : 1;
	req->tunnel_to_proxy = htonl(wr_ulp_mode |
				     FW_OFLD_TX_DATA_WR_SHOVE_V(val));
	req->plen = htonl(len);
	if (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT))
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
}
