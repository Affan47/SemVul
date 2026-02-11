gnac_on_converter_completion_cb(LibgnacConverter *converter)
{
  gnac_change_state(GNAC_AUDIO_READY_STATE);

  const gchar *msg;

  if (conversion_errors) {
    msg = _("Conversion completed with errors");
  } else {
    msg = _("Conversion completed");
  }

  gnac_ui_on_conversion_completed(msg);
  libgnac_debug(msg);
}
