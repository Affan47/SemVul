r8712_disassoc_cmd(struct _adapter *padapter)
{
	struct cmd_obj *pdisconnect_cmd;
	struct disconnect_parm *pdisconnect;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pdisconnect_cmd = kmalloc(sizeof(*pdisconnect_cmd), GFP_ATOMIC);
	if (pdisconnect_cmd == NULL)
		return _FAIL;
	pdisconnect = kmalloc(sizeof(*pdisconnect), GFP_ATOMIC);
	if (pdisconnect == NULL) {
		kfree(pdisconnect_cmd);
		return _FAIL;
	}
	init_h2fwcmd_w_parm_no_rsp(pdisconnect_cmd, pdisconnect,
				   _DisConnect_CMD_);
	r8712_enqueue_cmd(pcmdpriv, pdisconnect_cmd);
	return _SUCCESS;
}
