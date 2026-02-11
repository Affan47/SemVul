gm_pw_init_h323_page (GtkWidget *prefs_window,
                      GtkWidget *container)
{
  GtkWidget *entry = NULL;
  GtkWidget *subsection = NULL;

  const gchar *capabilities [] =
    {_("String"),
      _("Tone"),
      _("RFC2833"),
      _("Q.931"),
      NULL};

  const gchar *roles [] =
    { _("Disable H.239 Extended Video"),
      _("Allow H.239 per Content Role Mask"),
      _("Force H.239 Presentation Role"),
      _("Force H.239 Live Role"),
      NULL };


  subsection = gnome_prefs_subsection_new (prefs_window, container,
                                           _("Misc Settings"), 2, 2);

  entry =
    gnome_prefs_entry_new (subsection, _("Forward _URI:"), H323_KEY "forward_host", _("The host where calls should be forwarded if call forwarding is enabled"), 1, false);
  if (!g_strcmp0 (gtk_entry_get_text (GTK_ENTRY (entry)), ""))
    gtk_entry_set_text (GTK_ENTRY (entry), "h323:");


  subsection = gnome_prefs_subsection_new (prefs_window, container,
                                _("Advanced Settings"), 5, 1);


  gnome_prefs_toggle_new (subsection, _("Enable H.245 _tunneling"), H323_KEY "enable_h245_tunneling", _("This enables H.245 Tunneling mode. In H.245 Tunneling mode H.245 messages are encapsulated into the H.225 channel (port 1720). This saves one TCP connection during calls. H.245 Tunneling was introduced in H.323v2 and Netmeeting does not support it. Using both Fast Start and H.245 Tunneling can crash some versions of Netmeeting."), 0);

  gnome_prefs_toggle_new (subsection, _("Enable _early H.245"), H323_KEY "enable_early_h245", _("This enables H.245 early in the setup"), 1);

  gnome_prefs_toggle_new (subsection, _("Enable fast _start procedure"), H323_KEY "enable_fast_start", _("Connection will be established in Fast Start mode. Fast Start is a new way to start calls faster that was introduced in H.323v2. It is not supported by Netmeeting and using both Fast Start and H.245 Tunneling can crash some versions of Netmeeting."), 2);

  gnome_prefs_toggle_new (subsection, _("Enable H.239 control"), H323_KEY "enable_h239", _("This enables H.239 capability for additional video roles."), 3);

  gnome_prefs_int_option_menu_new (subsection, _("Extended Video Roles:"), roles, H323_KEY "video_role", _("Select the H.239 Video Role"), 4);


  subsection = gnome_prefs_subsection_new (prefs_window, container,
                                _("DTMF Mode"), 1, 1);

  gnome_prefs_int_option_menu_new (subsection, _("_Send DTMF as:"), capabilities, H323_KEY "dtmf_mode", _("Select the mode for DTMFs sending"), 0);
}
