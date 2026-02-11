pn533_rf_field(struct nfc_dev *nfc_dev, u8 rf)
{
	struct pn533 *dev = nfc_get_drvdata(nfc_dev);
	u8 rf_field = !!rf;
	int rc;

	rf_field |= PN533_CFGITEM_RF_FIELD_AUTO_RFCA;

	rc = pn533_set_configuration(dev, PN533_CFGITEM_RF_FIELD,
				     (u8 *)&rf_field, 1);
	if (rc) {
		nfc_err(&dev->interface->dev, "Error on setting RF field\n");
		return rc;
	}

	return rc;
}
