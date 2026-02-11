gupnp_service_action_set_value (GUPnPServiceAction *action,
                                const char         *argument,
                                const GValue       *value)
{
        g_return_if_fail (action != NULL);
        g_return_if_fail (argument != NULL);
        g_return_if_fail (value != NULL);

        if (action->msg->status_code == SOUP_STATUS_INTERNAL_SERVER_ERROR) {
                g_warning ("Calling gupnp_service_action_set_value() after "
                           "having called gupnp_service_action_return_error() "
                           "is not allowed.");

                return;
        }


        xml_util_start_element (action->response_str, argument);
        gvalue_util_value_append_to_xml_string (value, action->response_str);
        xml_util_end_element (action->response_str, argument);
}
