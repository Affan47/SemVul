ibus_input_pad_engine_destroy (IBusObject *object)
{
    IBusInputPadEngine *engine = (IBusInputPadEngine *) object;

    if (engine->prop_list) {
        g_object_unref (engine->prop_list);
        engine->prop_list = NULL;
    }
    if (engine->str_list) {
        free_str_list (engine->str_list);
        engine->str_list = NULL;
    }
    if (engine->window_data) {
        input_pad_window_destroy (engine->window_data);
        g_assert (engine->window_data == NULL);
    }
    IBUS_OBJECT_CLASS (parent_class)->destroy (object);
}
