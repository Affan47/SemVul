gnc_amount_edit_key_press(GtkWidget *widget, GdkEventKey *event)
{
    GNCAmountEdit *gae = GNC_AMOUNT_EDIT(widget);
    gint result;

#ifdef G_OS_WIN32

    if (event->hardware_keycode == VK_DECIMAL)
        event->keyval = GDK_KP_Decimal;
#endif
    if (event->keyval == GDK_KP_Decimal)
    {
        if (gae->print_info.monetary)
        {
            struct lconv *lc = gnc_localeconv ();
            event->keyval = lc->mon_decimal_point[0];
            event->string[0] = lc->mon_decimal_point[0];
        }
    }

    result = (* GTK_WIDGET_CLASS (parent_class)->key_press_event)(widget, event);

    switch (event->keyval)
    {
    case GDK_Return:
        if (gae->evaluate_on_enter)
            break;
        if (event->state & (GDK_CONTROL_MASK | GDK_MOD1_MASK | GDK_SHIFT_MASK))
            break;
        return result;
    case GDK_KP_Enter:
        break;
    default:
        return result;
    }

    gnc_amount_edit_evaluate (gae);

    return TRUE;
}
