usbctrl_vendorreq(struct adapter *adapt, u8 request, u16 value, u16 index, void *pdata, u16 len, u8 requesttype)
{
	struct dvobj_priv  *dvobjpriv = adapter_to_dvobj(adapt);
	struct usb_device *udev = dvobjpriv->pusbdev;
	unsigned int pipe;
	int status = 0;
	u8 reqtype;
	u8 *pIo_buf;
	int vendorreq_times = 0;

	if ((adapt->bSurpriseRemoved) || (adapt->pwrctrlpriv.pnp_bstop_trx)) {
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("usbctrl_vendorreq:(adapt->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n"));
		status = -EPERM;
		goto exit;
	}

	if (len > MAX_VENDOR_REQ_CMD_SIZE) {
		DBG_88E("[%s] Buffer len error ,vendor request failed\n", __func__);
		status = -EINVAL;
		goto exit;
	}

	if (mutex_lock_interruptible(&dvobjpriv->usb_vendor_req_mutex)) {
		status = -ERESTARTSYS;
		goto exit;
	}


	pIo_buf = dvobjpriv->usb_vendor_req_buf;

	if (pIo_buf == NULL) {
		DBG_88E("[%s] pIo_buf == NULL\n", __func__);
		status = -ENOMEM;
		goto release_mutex;
	}

	while (++vendorreq_times <= MAX_USBCTRL_VENDORREQ_TIMES) {
		memset(pIo_buf, 0, len);

		if (requesttype == 0x01) {
			pipe = usb_rcvctrlpipe(udev, 0);
			reqtype =  REALTEK_USB_VENQT_READ;
		} else {
			pipe = usb_sndctrlpipe(udev, 0);
			reqtype =  REALTEK_USB_VENQT_WRITE;
			memcpy(pIo_buf, pdata, len);
		}

		status = usb_control_msg(udev, pipe, request, reqtype, value, index, pIo_buf, len, RTW_USB_CONTROL_MSG_TIMEOUT);

		if (status == len) {
			if (requesttype == 0x01)
				memcpy(pdata, pIo_buf,  len);
		} else {
			DBG_88E("reg 0x%x, usb %s %u fail, status:%d value=0x%x, vendorreq_times:%d\n",
				value, (requesttype == 0x01) ? "read" : "write",
				len, status, *(u32 *)pdata, vendorreq_times);

			if (status < 0) {
				if (status == (-ESHUTDOWN) || status == -ENODEV) {
					adapt->bSurpriseRemoved = true;
				} else {
					struct hal_data_8188e	*haldata = GET_HAL_DATA(adapt);
					haldata->srestpriv.Wifi_Error_Status = USB_VEN_REQ_CMD_FAIL;
				}
			} else {
				if (status > 0) {
					if (requesttype == 0x01) {

						memcpy(pdata, pIo_buf,  len);
					}
				}
			}

		}


		if ((value >= FW_8188E_START_ADDRESS && value <= FW_8188E_END_ADDRESS) || status == len)
			break;
	}
release_mutex:
	mutex_unlock(&dvobjpriv->usb_vendor_req_mutex);
exit:
	return status;
}
