TXT_NewHorizBox(TXT_UNCAST_ARG(first_widget), ...)
{
    TXT_CAST_ARG(txt_widget_t, first_widget);
    txt_table_t *result;
    va_list args;
    int num_args;


    va_start(args, TXT_UNCAST_ARG_NAME(first_widget));

    num_args = 1;

    for (;;)
    {
        txt_widget_t *widget;

        widget = va_arg(args, txt_widget_t *);

        if (widget == NULL)
        {


            break;
        }
        else
        {
            ++num_args;
        }
    }

    va_end(args);


    result = TXT_NewTable(num_args);
    TXT_AddWidget(result, first_widget);


    va_start(args, TXT_UNCAST_ARG_NAME(first_widget));

    for (;;)
    {
        txt_widget_t *widget;

        widget = va_arg(args, txt_widget_t *);

        if (widget == NULL)
        {


            break;
        }
        else
        {
            TXT_AddWidget(result, widget);
        }
    }

    va_end(args);

    return result;
}
