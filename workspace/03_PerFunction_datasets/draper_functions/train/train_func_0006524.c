wm97xx_pen_irq_worker(struct work_struct *work)
{
	struct wm97xx *wm = container_of(work, struct wm97xx, pen_event_work);
	int pen_was_down = wm->pen_is_down;


	if (wm->id == WM9705_ID2) {
		if (wm97xx_reg_read(wm, AC97_WM97XX_DIGITISER_RD) &
					WM97XX_PEN_DOWN)
			wm->pen_is_down = 1;
		else
			wm->pen_is_down = 0;
	} else {
		u16 status, pol;
		mutex_lock(&wm->codec_mutex);
		status = wm97xx_reg_read(wm, AC97_GPIO_STATUS);
		pol = wm97xx_reg_read(wm, AC97_GPIO_POLARITY);

		if (WM97XX_GPIO_13 & pol & status) {
			wm->pen_is_down = 1;
			wm97xx_reg_write(wm, AC97_GPIO_POLARITY, pol &
						~WM97XX_GPIO_13);
		} else {
			wm->pen_is_down = 0;
			wm97xx_reg_write(wm, AC97_GPIO_POLARITY, pol |
					 WM97XX_GPIO_13);
		}

		if (wm->id == WM9712_ID2 && wm->variant != WM97xx_WM1613)
			wm97xx_reg_write(wm, AC97_GPIO_STATUS, (status &
						~WM97XX_GPIO_13) << 1);
		else
			wm97xx_reg_write(wm, AC97_GPIO_STATUS, status &
						~WM97XX_GPIO_13);
		mutex_unlock(&wm->codec_mutex);
	}


	if (!wm->mach_ops->acc_enabled || wm->mach_ops->acc_pen_down) {
		if (wm->pen_is_down && !pen_was_down) {

			queue_delayed_work(wm->ts_workq, &wm->ts_reader, 1);
		}


		if (!wm->pen_is_down && pen_was_down)
			wm->pen_is_down = 1;
	}

	if (!wm->pen_is_down && wm->mach_ops->acc_enabled)
		wm->mach_ops->acc_pen_up(wm);

	wm->mach_ops->irq_enable(wm, 1);
}
