_create_item_from_node (JsonNode *node)
{
  SwItem *item;
  JsonObject *root_o, *user_o, *geo_o = NULL;
  gchar *url;

  root_o = json_node_get_object (node);
  user_o = json_object_get_object_member (root_o, "user");

  if (json_object_has_member (root_o, "geo") &&
      !json_object_get_null_member (root_o, "geo"))
    geo_o = json_object_get_object_member (root_o, "geo");

  item = sw_item_new ();
  sw_item_put (item,
                "authorid",
                json_object_get_string_member (user_o, "screen_name"));

  url = g_strdup_printf ("http://twitter.com/%s/statuses/%lld",
                         json_object_get_string_member (user_o, "screen_name"),
                         (long long int)json_object_get_int_member (root_o, "id"));
  sw_item_put (item, "id", url);
  sw_item_take (item, "url", url);

  sw_item_put (item,
               "author",
               json_object_get_string_member (user_o, "name"));

  sw_item_put (item,
               "content",
               json_object_get_string_member (root_o, "text"));


  sw_item_take (item,
                "date",
                _make_date (json_object_get_string_member (root_o, "created_at")));

  if (json_object_has_member (user_o, "profile_image_url"))
  {
    sw_item_request_image_fetch (item,
                               TRUE,
                               "authoricon",
                               json_object_get_string_member (user_o, "profile_image_url"));
  }


  if (geo_o)
  {
    JsonArray *coords;

    coords = json_object_get_array_member (geo_o, "coordinates");
    sw_item_take (item,
                  "latitude",
                  g_strdup_printf ("%f",
                                   json_array_get_double_element (coords, 0)));
    sw_item_take (item,
                  "longitude",
                  g_strdup_printf ("%f",
                                   json_array_get_double_element (coords, 1)));
  }

  return item;
}
