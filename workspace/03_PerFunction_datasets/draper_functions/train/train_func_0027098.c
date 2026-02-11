gx_rack_tuner_set_display_flat(GxRackTuner *tuner, gboolean display_flat)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->display_flat = display_flat;
        if (display_flat) {
            tuner->note = note_flat;
        } else {
            tuner->note = note_sharp;
	}
	g_object_notify(G_OBJECT(tuner), "display_flat");
}
