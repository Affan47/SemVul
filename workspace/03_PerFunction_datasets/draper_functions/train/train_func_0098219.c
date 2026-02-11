open_xim()
{
  XIMTriggerKeys triggerKeys;

  im_styles.supported_styles = Styles;
  im_styles.count_styles = sizeof(Styles)/sizeof(Styles[0]);

  triggerKeys.count_keys = sizeof(trigger_keys)/sizeof(trigger_keys[0]);
  triggerKeys.keylist = trigger_keys;

  encodings.count_encodings = sizeof(chEncodings)/sizeof(XIMEncoding) - 1;
  encodings.supported_encodings = chEncodings;

  if ((xim_arr[0].xims = IMOpenIM(dpy,
          IMServerWindow,         xim_arr[0].xim_xwin,
          IMModifiers,            "Xi18n",
          IMServerName,           xim_arr[0].xim_server_name,
          IMLocale,               lc,
          IMServerTransport,      "X/",
          IMInputStyles,          &im_styles,
          IMEncodingList,         &encodings,
          IMProtocolHandler,      gcin_ProtoHandler,
          IMFilterEventMask,      KeyPressMask|KeyReleaseMask,
          IMOnKeysList, &triggerKeys,
          NULL)) == NULL) {
          p_err_no_alert("IMOpenIM '%s' failed. Maybe another XIM server is running.\n",
          xim_arr[0].xim_server_name);
  }
}
