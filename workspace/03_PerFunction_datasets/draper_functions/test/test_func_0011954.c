tda998x_destroy(struct tda998x_priv *priv)
{

	cec_write(priv, REG_CEC_RXSHPDINTENA, 0);
	reg_clear(priv, REG_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	if (priv->hdmi->irq)
		free_irq(priv->hdmi->irq, priv);

	del_timer_sync(&priv->edid_delay_timer);
	cancel_work_sync(&priv->detect_work);

	i2c_unregister_device(priv->cec);
}
