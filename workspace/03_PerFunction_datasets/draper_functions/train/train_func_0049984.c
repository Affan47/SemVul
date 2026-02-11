connect_proxy (GtkAction *action,
               GtkWidget *proxy)
{
        GtkToolButton *tool;
        GtkWidget *button;

	if (GTK_IS_TOOL_BUTTON (proxy)) {
                tool = GTK_TOOL_BUTTON (proxy);
                button = get_actual_button (tool);

                g_signal_connect (button, "button-press-event",
                                  G_CALLBACK (tool_button_press_cb), action);
                g_signal_connect (button, "button-release-event",
                                  G_CALLBACK (tool_button_release_cb), action);
        }

	(* GTK_ACTION_CLASS (nemo_navigation_action_parent_class)->connect_proxy) (action, proxy);
}
