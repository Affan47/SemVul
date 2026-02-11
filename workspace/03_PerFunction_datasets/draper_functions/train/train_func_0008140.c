si476x_core_cmd_am_rsq_status(struct si476x_core *core,
				  struct si476x_rsq_status_args *rsqargs,
				  struct si476x_rsq_status_report *report)
{
	int err;
	u8       resp[CMD_AM_RSQ_STATUS_NRESP];
	const u8 args[CMD_AM_RSQ_STATUS_NARGS] = {
		rsqargs->rsqack << 3 | rsqargs->attune << 2 |
		rsqargs->cancel << 1 | rsqargs->stcack,
	};

	err = si476x_core_send_command(core, CMD_AM_RSQ_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);


	if (!report)
		return err;

	report->snrhint		= 0x08 & resp[1];
	report->snrlint		= 0x04 & resp[1];
	report->rssihint	= 0x02 & resp[1];
	report->rssilint	= 0x01 & resp[1];

	report->bltf		= 0x80 & resp[2];
	report->snr_ready	= 0x20 & resp[2];
	report->rssiready	= 0x08 & resp[2];
	report->afcrl		= 0x02 & resp[2];
	report->valid		= 0x01 & resp[2];

	report->readfreq	= get_unaligned_be16(resp + 3);
	report->freqoff		= resp[5];
	report->rssi		= resp[6];
	report->snr		= resp[7];
	report->lassi		= resp[9];
	report->hassi		= resp[10];
	report->mult		= resp[11];
	report->dev		= resp[12];

	return err;
}
