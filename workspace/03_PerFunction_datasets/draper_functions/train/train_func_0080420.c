ecal_test_utils_cal_set_mode (ECal *cal,
                              CalMode mode,
                              GSourceFunc callback,
                              gpointer user_data)
{
	ECalTestClosure *closure;

	closure = g_new0 (ECalTestClosure, 1);
	closure->cb = callback;
	closure->user_data = user_data;

	g_signal_connect (G_OBJECT (cal), "cal_set_mode", G_CALLBACK (cal_set_mode_cb), closure);
	e_cal_set_mode (cal, mode);
}
