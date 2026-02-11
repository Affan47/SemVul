isp1362_hub_descriptor(struct isp1362_hcd *isp1362_hcd,
				   struct usb_hub_descriptor *desc)
{
	u32 reg = isp1362_hcd->rhdesca;

	DBG(3, "%s: enter\n", __func__);

	desc->bDescriptorType = USB_DT_HUB;
	desc->bDescLength = 9;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = reg & 0x3;

	desc->wHubCharacteristics = cpu_to_le16((reg >> 8) &
						(HUB_CHAR_LPSM |
						 HUB_CHAR_COMPOUND |
						 HUB_CHAR_OCPM));
	DBG(0, "%s: hubcharacteristics = %02x\n", __func__,
			desc->wHubCharacteristics);
	desc->bPwrOn2PwrGood = (reg >> 24) & 0xff;

	desc->u.hs.DeviceRemovable[0] = desc->bNbrPorts == 1 ? 1 << 1 : 3 << 1;
	desc->u.hs.DeviceRemovable[1] = ~0;

	DBG(3, "%s: exit\n", __func__);
}
