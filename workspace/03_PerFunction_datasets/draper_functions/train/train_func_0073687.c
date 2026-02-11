create_dialog_about (void)
{
  gchar **authors = read_authors();
  const gchar *documenters[] = {
    "Sridhar Ratnakumar (sridhar.ratna@gmail.com)",
    NULL
  };

  gchar *name = "GNUSim8085";
  gchar *copyright = "Copyright (C) 2003 Sridhar Ratnakumar";
  gchar *comments = "8085 Microprocessor Simulator";
  gchar *translators = _("translator_credits");
  GdkPixbuf *dialog_about_logo_pixbuf;
  GdkPixbuf *dialog_about_icon_pixbuf;

  if (!strcmp (translators, "translator_credits"))
    translators = NULL;
  dialog_about_logo_pixbuf = create_pixbuf ("gnusim8085.svg");
  if (!dialog_about_logo_pixbuf)
    dialog_about_logo_pixbuf = create_pixbuf ("gnusim8085.ico");

  dialog_about_icon_pixbuf = create_pixbuf ("gnusim8085.svg");
  if (!dialog_about_icon_pixbuf)
    dialog_about_icon_pixbuf = create_pixbuf ("gnusim8085.ico");

  gtk_show_about_dialog (NULL,
						 "name", name,
						 "version", VERSION,
						 "comments", comments,
						 "copyright", copyright,
						 "website", PACKAGE_URL,
						 "logo", dialog_about_logo_pixbuf,
						 "icon", dialog_about_icon_pixbuf,
						 "authors", authors,
						 "documenters", documenters,
						 "translator-credits", translators,
						 "border-width", 5,
						 NULL);

  if (dialog_about_icon_pixbuf)
	g_object_unref (dialog_about_icon_pixbuf);

  if (dialog_about_logo_pixbuf)
	g_object_unref (dialog_about_logo_pixbuf);
}
