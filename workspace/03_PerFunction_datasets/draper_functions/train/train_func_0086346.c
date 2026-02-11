received_discovery_response (GSSDPResourceBrowser *resource_browser,
                             SoupMessageHeaders   *headers)
{
        const char *st;

        st = soup_message_headers_get_one (headers, "ST");
        if (!st)
                return;

        if (!check_target_compat (resource_browser, st))
                return;

        resource_available (resource_browser, headers);
}
