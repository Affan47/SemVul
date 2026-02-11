gg_svg_add_clip_url (struct gg_svg_style *style, const char *url)
{

    int len;
    if (style->clip_url != NULL)
	free (style->clip_url);
    if (url == NULL)
      {
	  style->clip_url = NULL;
	  return;
      }
    len = strlen (url);
    style->clip_url = malloc (len + 1);
    strcpy (style->clip_url, url);
}
