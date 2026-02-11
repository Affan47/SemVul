b43legacy_op_remove_interface(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev = wl->current_dev;
	unsigned long flags;

	b43legacydbg(wl, "Removing Interface type %d\n", vif->type);

	mutex_lock(&wl->mutex);

	B43legacy_WARN_ON(!wl->operating);
	B43legacy_WARN_ON(wl->vif != vif);
	wl->vif = NULL;

	wl->operating = false;

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_adjust_opmode(dev);
	eth_zero_addr(wl->mac_addr);
	b43legacy_upload_card_macaddress(dev);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	mutex_unlock(&wl->mutex);
}
