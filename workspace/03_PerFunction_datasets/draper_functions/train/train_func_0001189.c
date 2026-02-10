imx6ul_tsc_init(struct imx6ul_tsc *tsc)
{
	int err;

	err = imx6ul_adc_init(tsc);
	if (err)
		return err;
	imx6ul_tsc_channel_config(tsc);
	imx6ul_tsc_set(tsc);

	return 0;
}
