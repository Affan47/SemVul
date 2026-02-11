bus_input_context_update_lookup_table (BusInputContext *context,
                                       IBusLookupTable *table,
                                       gboolean         visible)
{
    g_assert (BUS_IS_INPUT_CONTEXT (context));

    if (context->lookup_table) {
        g_object_unref (context->lookup_table);
    }

    context->lookup_table = (IBusLookupTable *) g_object_ref_sink (table ? table : lookup_table_empty);
    context->lookup_table_visible = visible;

    if (context->capabilities & IBUS_CAP_LOOKUP_TABLE) {
        GVariant *variant = ibus_serializable_serialize ((IBusSerializable *)table);
        bus_input_context_emit_signal (context,
                                       "UpdateLookupTable",
                                       g_variant_new ("(vb)", variant, visible),
                                       NULL);
    }
    else {
        g_signal_emit (context,
                       context_signals[UPDATE_LOOKUP_TABLE],
                       0,
                       context->lookup_table,
                       context->lookup_table_visible);
    }
}
