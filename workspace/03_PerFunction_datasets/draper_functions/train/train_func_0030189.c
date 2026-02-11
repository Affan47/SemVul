rtw_enqueue_cmd(struct cmd_priv *pcmdpriv, struct cmd_obj *cmd_obj)
{
	int res = _FAIL;
	struct adapter *padapter = pcmdpriv->padapter;


	if (cmd_obj == NULL)
		goto exit;

	cmd_obj->padapter = padapter;

	res = rtw_cmd_filter(pcmdpriv, cmd_obj);
	if (res == _FAIL) {
		rtw_free_cmd_obj(cmd_obj);
		goto exit;
	}

	res = _rtw_enqueue_cmd(&pcmdpriv->cmd_queue, cmd_obj);

	if (res == _SUCCESS)
		up(&pcmdpriv->cmd_queue_sema);

exit:


	return res;
}
