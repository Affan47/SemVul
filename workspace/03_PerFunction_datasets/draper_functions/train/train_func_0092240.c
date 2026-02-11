run_action_dialog (GUPnPServiceActionInfo    *action_info,
                   GUPnPServiceProxy         *proxy,
                   GUPnPServiceIntrospection *introspection)
{
        GList *in_arguments;
        GList *out_arguments;

        setup_action_dialog_labels (GUPNP_SERVICE_INFO (proxy), action_info);

        in_arguments = find_arguments_by_direction (
                        action_info->arguments,
                        GUPNP_SERVICE_ACTION_ARG_DIRECTION_IN);
        populate_action_arguments_table (
                        in_args_table,
                        in_arguments,
                        GUPNP_SERVICE_ACTION_ARG_DIRECTION_IN,
                        introspection);

        out_arguments = find_arguments_by_direction (
                        action_info->arguments,
                        GUPNP_SERVICE_ACTION_ARG_DIRECTION_OUT);
        populate_action_arguments_table (
                        out_args_table,
                        out_arguments,
                        GUPNP_SERVICE_ACTION_ARG_DIRECTION_OUT,
                        introspection);


        if (!in_arguments)
                gtk_expander_set_expanded (GTK_EXPANDER (out_args_expander), TRUE);

        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_hide (dialog);

}
