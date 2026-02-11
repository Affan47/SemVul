wm8350_mic_handler(int irq, void *data)
{
	struct wm8350_data *priv = data;
	struct wm8350 *wm8350 = priv->wm8350;
	u16 reg;
	int report = 0;

#ifndef CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 mic");
#endif

	reg = wm8350_reg_read(wm8350, WM8350_JACK_PIN_STATUS);
	if (reg & WM8350_JACK_MICSCD_LVL)
		report |= priv->mic.short_report;
	if (reg & WM8350_JACK_MICSD_LVL)
		report |= priv->mic.report;

	snd_soc_jack_report(priv->mic.jack, report,
			    priv->mic.report | priv->mic.short_report);

	return IRQ_HANDLED;
}
