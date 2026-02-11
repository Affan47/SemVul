_r8712_join_timeout_handler(struct _adapter *adapter)
{
	unsigned long irqL;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;

	if (adapter->bDriverStopped || adapter->bSurpriseRemoved)
		return;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
	pmlmepriv->to_join = false;
	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		r8712_os_indicate_disconnect(adapter);
		_clr_fwstate_(pmlmepriv, _FW_LINKED);
	}
	if (adapter->pwrctrlpriv.pwr_mode != adapter->registrypriv.power_mgnt) {
		r8712_set_ps_mode(adapter, adapter->registrypriv.power_mgnt,
				  adapter->registrypriv.smart_ps);
	}
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
}
