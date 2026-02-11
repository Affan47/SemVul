ario_dnd_tree_new (const GtkTargetEntry* targets,
                   const gint n_targets,
                   const gboolean browse_mode)
{
        ARIO_LOG_FUNCTION_START;
        ArioDndTree *dnd_tree;

        dnd_tree = g_object_new (TYPE_ARIO_DND_TREE, NULL);
        g_return_val_if_fail (dnd_tree->priv, NULL);


        gtk_drag_source_set (GTK_WIDGET (dnd_tree),
                             GDK_BUTTON1_MASK,
                             targets,
                             n_targets,
                             GDK_ACTION_MOVE | GDK_ACTION_COPY);

        dnd_tree->priv->browse_mode = browse_mode;


        g_signal_connect (dnd_tree,
                          "button_press_event",
                          G_CALLBACK (ario_dnd_tree_button_press_cb),
                          dnd_tree);
        g_signal_connect (dnd_tree,
                          "button_release_event",
                          G_CALLBACK (ario_dnd_tree_button_release_cb),
                          dnd_tree);
        g_signal_connect (dnd_tree,
                          "motion_notify_event",
                          G_CALLBACK (ario_dnd_tree_motion_notify),
                          dnd_tree);

        return GTK_WIDGET (dnd_tree);
}
