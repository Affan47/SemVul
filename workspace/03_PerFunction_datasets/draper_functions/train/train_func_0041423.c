fp_verify_finger_img(struct fp_dev *dev,
	struct fp_print_data *enrolled_print, struct fp_img **img)
{
	struct sync_verify_data *vdata;
	gboolean stopped = FALSE;
	int r;

	if (!enrolled_print) {
		fp_err("no print given");
		return -EINVAL;
	}

	if (!fp_dev_supports_print_data(dev, enrolled_print)) {
		fp_err("print is not compatible with device");
		return -EINVAL;
	}

	fp_dbg("to be handled by %s", dev->drv->name);
	vdata = g_malloc0(sizeof(struct sync_verify_data));
	r = fp_async_verify_start(dev, enrolled_print, sync_verify_cb, vdata);
	if (r < 0) {
		fp_dbg("verify_start error %d", r);
		g_free(vdata);
		return r;
	}

	while (!vdata->populated) {
		r = fp_handle_events();
		if (r < 0) {
			g_free(vdata);
			goto err;
		}
	}

	if (img)
		*img = vdata->img;
	else
		fp_img_free(vdata->img);

	r = vdata->result;
	g_free(vdata);
	switch (r) {
	case FP_VERIFY_NO_MATCH:
		fp_dbg("result: no match");
		break;
	case FP_VERIFY_MATCH:
		fp_dbg("result: match");
		break;
	case FP_VERIFY_RETRY:
		fp_dbg("verify should retry");
		break;
	case FP_VERIFY_RETRY_TOO_SHORT:
		fp_dbg("swipe was too short, verify should retry");
		break;
	case FP_VERIFY_RETRY_CENTER_FINGER:
		fp_dbg("finger was not centered, verify should retry");
		break;
	case FP_VERIFY_RETRY_REMOVE_FINGER:
		fp_dbg("scan failed, remove finger and retry");
		break;
	default:
		fp_err("unrecognised return code %d", r);
		r = -EINVAL;
	}

err:
	fp_dbg("ending verification");
	if (fp_async_verify_stop(dev, verify_stop_cb, &stopped) == 0)
		while (!stopped)
			if (fp_handle_events() < 0)
				break;

	return r;
}
