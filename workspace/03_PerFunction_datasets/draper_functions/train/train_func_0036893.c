get_hac_lag (int T)
{
    int h = 0;

    check_for_state();


    if (state->ropts.user_lag >= 0 && state->ropts.user_lag < T - 2) {

	h = state->ropts.user_lag;
    } else if (state->ropts.auto_lag == AUTO_LAG_WOOLDRIDGE) {
	h = 4.0 * pow(T / 100.0, 2.0 / 9.0);
    } else {

	h = 0.75 * pow(T, 1.0 / 3.0);
    }

    return h;
}
