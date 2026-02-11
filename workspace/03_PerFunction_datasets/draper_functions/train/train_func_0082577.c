bq2415x_update_reported_mode(struct bq2415x_device *bq, int mA)
{
	enum bq2415x_mode mode;

	if (mA == 0)
		mode = BQ2415X_MODE_OFF;
	else if (mA < 500)
		mode = BQ2415X_MODE_NONE;
	else if (mA < 1800)
		mode = BQ2415X_MODE_HOST_CHARGER;
	else
		mode = BQ2415X_MODE_DEDICATED_CHARGER;

	if (bq->reported_mode == mode)
		return false;

	bq->reported_mode = mode;
	return true;
}
