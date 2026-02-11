da9150_fg_soc_event_config(struct da9150_fg *fg)
{
	int soc;

	soc = da9150_fg_read_attr_sync(fg, DA9150_QIF_SOC_PCT,
				       DA9150_QIF_SOC_PCT_SIZE);

	if (soc > fg->warn_soc) {

		da9150_fg_write_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->warn_soc + 1);
	} else if ((soc <= fg->warn_soc) && (soc > fg->crit_soc)) {


		da9150_fg_write_attr_sync(fg, DA9150_QIF_DISCHARGE_LIMIT,
					  DA9150_QIF_DISCHARGE_LIMIT_SIZE,
					  fg->crit_soc + 1);

		da9150_fg_write_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->warn_soc);
	} else if (soc <= fg->crit_soc) {

		da9150_fg_write_attr_sync(fg, DA9150_QIF_CHARGE_LIMIT,
					  DA9150_QIF_CHARGE_LIMIT_SIZE,
					  fg->crit_soc);
	}
}
