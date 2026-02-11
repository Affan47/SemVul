amitk_volume_set_corner(AmitkVolume * volume, AmitkPoint corner) {

  g_return_if_fail(AMITK_IS_VOLUME(volume));

  if (!POINT_EQUAL(AMITK_VOLUME_CORNER(volume), corner) || (!AMITK_VOLUME_VALID(volume))) {
    g_signal_emit(G_OBJECT(volume), volume_signals[VOLUME_CORNER_CHANGED], 0, &corner);
    g_signal_emit(G_OBJECT(volume), volume_signals[VOLUME_CHANGED], 0);
  }
}
