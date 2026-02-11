wm831x_ts_pen_down_irq(int irq, void *irq_data)
{
	struct wm831x_ts *wm831x_ts = irq_data;
	struct wm831x *wm831x = wm831x_ts->wm831x;
	int ena = 0;

	if (wm831x_ts->pen_down)
		return IRQ_HANDLED;

	disable_irq_nosync(wm831x_ts->pd_irq);


	if (wm831x_ts->pressure)
		ena |= WM831X_TCH_Z_ENA;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | WM831X_TCH_Z_ENA,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | ena);

	wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
			WM831X_TCHPD_EINT, WM831X_TCHPD_EINT);

	wm831x_ts->pen_down = true;


	dev_dbg(wm831x->dev, "IRQ PD->DATA\n");
	schedule_work(&wm831x_ts->pd_data_work);

	return IRQ_HANDLED;
}
