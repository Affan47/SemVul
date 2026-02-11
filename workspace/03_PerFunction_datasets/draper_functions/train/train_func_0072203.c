amitk_line_profile_set_start_point(AmitkLineProfile * line_profile,
					const AmitkPoint start_point) {

  g_return_if_fail(AMITK_IS_LINE_PROFILE(line_profile));

  if (!POINT_EQUAL(AMITK_LINE_PROFILE_START_POINT(line_profile), start_point)) {
    line_profile->start_point = start_point;
    g_signal_emit(G_OBJECT(line_profile), line_profile_signals[LINE_PROFILE_CHANGED], 0);
  }

  return;
}
