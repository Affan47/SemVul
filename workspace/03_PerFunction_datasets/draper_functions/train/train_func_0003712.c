rtw_disassoc_cmd23a_callback(struct rtw_adapter *padapter,
				  struct cmd_obj *pcmd)
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (pcmd->res != H2C_SUCCESS) {
		spin_lock_bh(&pmlmepriv->lock);
		set_fwstate(pmlmepriv, _FW_LINKED);
		spin_unlock_bh(&pmlmepriv->lock);
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 "***Error: disconnect_cmd_callback Fail ***\n");
		return;
	}


	rtw_free_cmd_obj23a(pcmd);
}
