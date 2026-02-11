r8712_addbareq_cmd(struct _adapter *padapter, u8 tid)
{
	struct cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj		*ph2c;
	struct addBaReq_parm	*paddbareq_parm;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (ph2c == NULL)
		return _FAIL;
	paddbareq_parm = kmalloc(sizeof(*paddbareq_parm), GFP_ATOMIC);
	if (paddbareq_parm == NULL) {
		kfree(ph2c);
		return _FAIL;
	}
	paddbareq_parm->tid = tid;
	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm,
				   GEN_CMD_CODE(_AddBAReq));
	r8712_enqueue_cmd_ex(pcmdpriv, ph2c);
	return _SUCCESS;
}
