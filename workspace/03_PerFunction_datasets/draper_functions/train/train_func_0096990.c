test_patternm_destroy(struct cpssp *cpssp)
{
	unsigned int i;
	patternm_destroy(cpssp->comp_patternm);

	sig_opt_rgb_destroy(cpssp->video_out);
	for (i = 0; i < 16; i++) {
		sig_match_destroy(cpssp->match_inout[i]);
	}

	for (i = 0; i < 8; i++) {
		sig_boolean_destroy(cpssp->text_pm[i].result_in);
		sig_string_destroy(cpssp->text_pm[i].text_out);
	}

	for (i = 0; i < 4; i++) {
		sig_string_destroy(cpssp->gfx[i].pattern_rectangle);
		sig_integer_destroy(cpssp->gfx[i].match_rectangle_x);
		sig_integer_destroy(cpssp->gfx[i].match_rectangle_y);
		sig_integer_destroy(cpssp->gfx[i].match_rectangle_w);
		sig_integer_destroy(cpssp->gfx[i].match_rectangle_h);
	}

	shm_free(cpssp);
}
