make_item (SwLastfmItemView *item_view,
           SwService        *service,
           RestXmlNode      *user,
           RestXmlNode      *track)
{
  RestXmlNode *date;
  SwItem *item;
  const char *s;
  char *id;

  item = sw_item_new ();
  sw_item_set_service (item, service);

  id = g_strdup_printf ("%s %s",
                        rest_xml_node_find (track, "url")->content,
                        rest_xml_node_find (user, "name")->content);
  sw_item_take (item, "id", id);
  sw_item_put (item, "url", rest_xml_node_find (track, "url")->content);
  sw_item_take (item, "title", make_title (track));
  sw_item_put (item, "album", rest_xml_node_find (track, "album")->content);

  get_thumbnail (item_view, item, track);

  date = rest_xml_node_find (track, "date");
  if (date) {
    sw_item_take (item, "date", sw_time_t_to_string (atoi (rest_xml_node_get_attr (date, "uts"))));
  } else {

    sw_item_take (item, "date", sw_time_t_to_string (time (NULL)));
  }

  s = rest_xml_node_find (user, "realname")->content;
  if (s) {
    sw_item_put (item, "author", s);
  } else {
    sw_item_put (item, "author", rest_xml_node_find (user, "name")->content);
  }

  sw_item_put (item, "authorid", rest_xml_node_find (user, "name")->content);

  s = get_image_url (user, "medium");
  if (s)
    sw_item_request_image_fetch (item, FALSE, "authoricon", s);

  s = get_image_url (user, "large");
  if (s)
    sw_item_request_image_fetch (item, FALSE, "authoricon_large", s);

  return item;
}
