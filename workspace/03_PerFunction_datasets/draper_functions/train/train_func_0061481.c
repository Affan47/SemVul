ibus_input_pad_engine_focus_in (IBusEngine *engine)
{
    IBusInputPadEngine *input_pad = (IBusInputPadEngine *) engine;

    ibus_engine_register_properties (engine, input_pad->prop_list);

    parent_class->focus_in (engine);

    input_pad->window_data = input_pad_window;
    if (input_pad->window_data == NULL) {
        return;
    }

    g_signal_connect (G_OBJECT (input_pad->window_data),
                      "button-pressed",
                      G_CALLBACK (on_window_button_pressed), (gpointer) engine);
    input_pad_window_reorder_button_pressed (input_pad->window_data);
}
