sidebar_complete_idle (DhSidebar *self)
{
        const gchar  *str;
        gchar        *completed = NULL;
        gsize         length;

        str = gtk_entry_get_text (GTK_ENTRY (self->priv->entry));

        g_completion_complete (self->priv->completion, str, &completed);
        if (completed) {
                length = strlen (str);

                gtk_entry_set_text (GTK_ENTRY (self->priv->entry), completed);
                gtk_editable_set_position (GTK_EDITABLE (self->priv->entry), length);
                gtk_editable_select_region (GTK_EDITABLE (self->priv->entry),
                                            length, -1);
                g_free (completed);
        }

        self->priv->idle_complete = 0;

        return FALSE;
}
