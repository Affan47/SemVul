TXT_EmitSignal(TXT_UNCAST_ARG(widget), const char *signal_name)
{
    TXT_CAST_ARG(txt_widget_t, widget);
    txt_callback_table_t *table;
    int i;

    table = widget->callback_table;


    TXT_RefCallbackTable(table);


    for (i=0; i<table->num_callbacks; ++i)
    {
        if (!strcmp(table->callbacks[i].signal_name, signal_name))
        {
            table->callbacks[i].func(widget, table->callbacks[i].user_data);
        }
    }


    TXT_UnrefCallbackTable(table);
}
