__synaptics_init(struct psmouse *psmouse, bool absolute_mode)
{
	struct synaptics_data *priv;
	int err = -1;


	if (absolute_mode && broken_olpc_ec) {
		psmouse_info(psmouse,
			     "OLPC XO detected, not enabling Synaptics protocol.\n");
		return -ENODEV;
	}

	psmouse->private = priv = kzalloc(sizeof(struct synaptics_data), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	psmouse_reset(psmouse);

	if (synaptics_query_hardware(psmouse)) {
		psmouse_err(psmouse, "Unable to query device.\n");
		goto init_fail;
	}

	priv->absolute_mode = absolute_mode;
	if (SYN_ID_DISGEST_SUPPORTED(priv->identity))
		priv->disable_gesture = true;


	priv->is_forcepad = psmouse_matches_pnp_id(psmouse, forcepad_pnp_ids);

	if (synaptics_set_mode(psmouse)) {
		psmouse_err(psmouse, "Unable to initialize device.\n");
		goto init_fail;
	}

	priv->pkt_type = SYN_MODEL_NEWABS(priv->model_id) ? SYN_NEWABS : SYN_OLDABS;

	psmouse_info(psmouse,
		     "Touchpad model: %ld, fw: %ld.%ld, id: %#lx, caps: %#lx/%#lx/%#lx/%#lx, board id: %lu, fw id: %lu\n",
		     SYN_ID_MODEL(priv->identity),
		     SYN_ID_MAJOR(priv->identity), SYN_ID_MINOR(priv->identity),
		     priv->model_id,
		     priv->capabilities, priv->ext_cap, priv->ext_cap_0c,
		     priv->ext_cap_10, priv->board_id, priv->firmware_id);

	set_input_params(psmouse, priv);


	psmouse->model = ((priv->model_id & 0x00ff0000) >> 8) |
			  (priv->model_id & 0x000000ff);

	if (absolute_mode) {
		psmouse->protocol_handler = synaptics_process_byte;
		psmouse->pktsize = 6;
	} else {

		psmouse->protocol_handler = psmouse_process_byte;
		psmouse->pktsize = 3;
	}

	psmouse->set_rate = synaptics_set_rate;
	psmouse->disconnect = synaptics_disconnect;
	psmouse->reconnect = synaptics_reconnect;
	psmouse->cleanup = synaptics_reset;

	psmouse->resync_time = 0;

	if (SYN_CAP_PASS_THROUGH(priv->capabilities))
		synaptics_pt_create(psmouse);


	if (psmouse->rate >= 80 && impaired_toshiba_kbc) {
		psmouse_info(psmouse,
			     "Toshiba %s detected, limiting rate to 40pps.\n",
			     dmi_get_system_info(DMI_PRODUCT_NAME));
		psmouse->rate = 40;
	}

	if (!priv->absolute_mode && SYN_ID_DISGEST_SUPPORTED(priv->identity)) {
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_disable_gesture.dattr);
		if (err) {
			psmouse_err(psmouse,
				    "Failed to create disable_gesture attribute (%d)",
				    err);
			goto init_fail;
		}
	}

	return 0;

 init_fail:
	kfree(priv);
	return err;
}
