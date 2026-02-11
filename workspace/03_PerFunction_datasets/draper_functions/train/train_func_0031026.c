gx_rack_tuner_set_freq(GxRackTuner *tuner, double freq)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->parent.freq = freq;
	g_object_notify(G_OBJECT(tuner), "freq");
}
