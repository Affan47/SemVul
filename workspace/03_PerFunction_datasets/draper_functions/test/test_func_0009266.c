gr_set_clip_ps_off()
{
	if (_clipping_postscript) {
		fprintf(_grPS, "S Q %% turn clipping off\n");
		check_psfile();
		_clipping_postscript = false;
	}
}
