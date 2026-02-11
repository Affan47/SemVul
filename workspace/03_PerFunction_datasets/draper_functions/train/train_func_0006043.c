bus_input_context_clear_preedit_text (BusInputContext *context)
{
    g_assert (BUS_IS_INPUT_CONTEXT (context));

    if (context->preedit_visible &&
        context->preedit_mode == IBUS_ENGINE_PREEDIT_COMMIT) {
        bus_input_context_commit_text (context, context->preedit_text);
    }


    bus_input_context_update_preedit_text (context,
        text_empty, 0, FALSE, IBUS_ENGINE_PREEDIT_CLEAR);
}
