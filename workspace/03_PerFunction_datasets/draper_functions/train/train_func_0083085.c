print_favourites (RestProxy *proxy)
{
  RestProxyCall *call;
  RestXmlNode *root, *node;

  call = rest_proxy_new_call (proxy);
  rest_proxy_call_set_function (call, "flickr.favorites.getList");
  rest_proxy_call_add_param (call, "extras", "owner_name");
  rest_proxy_call_add_param (call, "per_page", "10");

  if (!rest_proxy_call_sync (call, NULL))
    g_error ("Cannot get favourites");

  root = get_xml (call);

  for (node = rest_xml_node_find (root, "photo"); node; node = node->next) {
    g_print ("%s by %s\n",
             rest_xml_node_get_attr (node, "title"),
             rest_xml_node_get_attr (node, "ownername"));
  }

  rest_xml_node_unref (root);
}
