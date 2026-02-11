rtw_select_queue(struct net_device *dev, struct sk_buff *skb,
			    void *accel_priv,
			    select_queue_fallback_t fallback)
{
	struct rtw_adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	skb->priority = rtw_classify8021d(skb);

	if (pmlmepriv->acm_mask != 0)
		skb->priority = qos_acm23a(pmlmepriv->acm_mask, skb->priority);
	return rtw_1d_to_queue[skb->priority];
}
