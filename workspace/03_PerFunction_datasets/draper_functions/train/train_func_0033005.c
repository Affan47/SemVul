ar5523_read_reply(struct ar5523 *ar, struct ar5523_cmd_hdr *hdr,
			      struct ar5523_tx_cmd *cmd)
{
	int dlen, olen;
	__be32 *rp;

	dlen = be32_to_cpu(hdr->len) - sizeof(*hdr);

	if (dlen < 0) {
		WARN_ON(1);
		goto out;
	}

	ar5523_dbg(ar, "Code = %d len = %d\n", be32_to_cpu(hdr->code) & 0xff,
		   dlen);

	rp = (__be32 *)(hdr + 1);
	if (dlen >= sizeof(u32)) {
		olen = be32_to_cpu(rp[0]);
		dlen -= sizeof(u32);
		if (olen == 0) {

			olen = sizeof(u32);
		}
	} else
		olen = 0;

	if (cmd->odata) {
		if (cmd->olen < olen) {
			ar5523_err(ar, "olen to small %d < %d\n",
				   cmd->olen, olen);
			cmd->olen = 0;
			cmd->res = -EOVERFLOW;
		} else {
			cmd->olen = olen;
			memcpy(cmd->odata, &rp[1], olen);
			cmd->res = 0;
		}
	}

out:
	complete(&cmd->done);
}
