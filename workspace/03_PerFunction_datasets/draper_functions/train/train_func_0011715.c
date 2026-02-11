synaptics_report_mt_data(struct psmouse *psmouse,
				     const struct synaptics_hw_state *sgm,
				     int num_fingers)
{
	struct input_dev *dev = psmouse->dev;
	struct synaptics_data *priv = psmouse->private;
	const struct synaptics_hw_state *hw[2] = { sgm, &priv->agm };
	struct input_mt_pos pos[2];
	int slot[2], nsemi, i;

	nsemi = clamp_val(num_fingers, 0, 2);

	for (i = 0; i < nsemi; i++) {
		pos[i].x = hw[i]->x;
		pos[i].y = synaptics_invert_y(hw[i]->y);
	}

	input_mt_assign_slots(dev, slot, pos, nsemi, DMAX * priv->x_res);

	for (i = 0; i < nsemi; i++) {
		input_mt_slot(dev, slot[i]);
		input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);
		input_report_abs(dev, ABS_MT_POSITION_X, pos[i].x);
		input_report_abs(dev, ABS_MT_POSITION_Y, pos[i].y);
		input_report_abs(dev, ABS_MT_PRESSURE, hw[i]->z);
	}

	input_mt_drop_unused(dev);


	input_mt_report_pointer_emulation(dev, false);


	input_mt_report_finger_count(dev, num_fingers);

	synaptics_report_buttons(psmouse, sgm);

	input_sync(dev);
}
