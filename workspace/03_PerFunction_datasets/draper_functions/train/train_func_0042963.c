rtw_addbareq_cmd(struct adapter *padapter, u8 tid, u8 *addr)
{
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj *ph2c;
	struct addBaReq_parm *paddbareq_parm;
	u8	res = _SUCCESS;


	ph2c = kzalloc(sizeof(struct cmd_obj), GFP_ATOMIC);
	if (ph2c == NULL) {
		res = _FAIL;
		goto exit;
	}

	paddbareq_parm = kzalloc(sizeof(struct addBaReq_parm), GFP_ATOMIC);
	if (paddbareq_parm == NULL) {
		kfree(ph2c);
		res = _FAIL;
		goto exit;
	}

	paddbareq_parm->tid = tid;
	memcpy(paddbareq_parm->addr, addr, ETH_ALEN);

	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm, GEN_CMD_CODE(_AddBAReq));


	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

exit:


	return res;
}
