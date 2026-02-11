encx24j600_set_rxfilter_mode(struct encx24j600_priv *priv)
{
	switch (priv->rxfilter) {
	case RXFILTER_PROMISC:
		encx24j600_set_bits(priv, MACON1, PASSALL);
		encx24j600_write_reg(priv, ERXFCON, UCEN | MCEN | NOTMEEN);
		break;
	case RXFILTER_MULTI:
		encx24j600_clr_bits(priv, MACON1, PASSALL);
		encx24j600_write_reg(priv, ERXFCON, UCEN | CRCEN | BCEN | MCEN);
		break;
	case RXFILTER_NORMAL:
	default:
		encx24j600_clr_bits(priv, MACON1, PASSALL);
		encx24j600_write_reg(priv, ERXFCON, UCEN | CRCEN | BCEN);
		break;
	}
}
