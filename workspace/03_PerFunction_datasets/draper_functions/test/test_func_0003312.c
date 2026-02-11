ibus_input_context_set_surrounding_text (IBusInputContext   *context,
                                         IBusText           *text,
                                         guint32             cursor_pos,
                                         guint32             anchor_pos)
{
    g_assert (IBUS_IS_INPUT_CONTEXT (context));
    g_assert (IBUS_IS_TEXT (text));

    IBusInputContextPrivate *priv;
    priv = IBUS_INPUT_CONTEXT_GET_PRIVATE (context);

    if (cursor_pos != priv->surrounding_cursor_pos ||
        anchor_pos != priv->selection_anchor_pos ||
        priv->surrounding_text == NULL ||
        g_strcmp0 (text->text, priv->surrounding_text->text) != 0) {
        if (priv->surrounding_text)
            g_object_unref (priv->surrounding_text);
        priv->surrounding_text = (IBusText *) g_object_ref_sink (text);
        priv->surrounding_cursor_pos = cursor_pos;
        priv->selection_anchor_pos = anchor_pos;

        if (priv->needs_surrounding_text) {
            GVariant *variant = ibus_serializable_serialize ((IBusSerializable *)text);
            g_dbus_proxy_call ((GDBusProxy *) context,
                               "SetSurroundingText",
                               g_variant_new ("(vuu)",
                                              variant,
                                              cursor_pos,
                                              anchor_pos),
                                G_DBUS_CALL_FLAGS_NONE,
                                -1,
                                NULL,
                                NULL,
                                NULL
                                );
        }
    }
}
