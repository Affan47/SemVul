bus_match_rule_connection_destroy_cb (BusConnection *connection,
                                      BusMatchRule  *rule)
{
    GList *p;
    for (p = rule->recipients; p != NULL; p = p->next) {
        BusRecipient *recipient = (BusRecipient *)p->data;

        if (recipient->connection == connection) {
            rule->recipients = g_list_remove_link (rule->recipients, p);
            bus_recipient_free (recipient);
            return;
        }

        if (rule->recipients == NULL) {
            ibus_object_destroy (IBUS_OBJECT (rule));
        }
    }
    g_assert_not_reached ();
}
