arithmetic_expr_changed(GtkWidget *entry,
                        ArithmeticControls *controls)
{
    ArithmeticArgs *args;
    GtkComboBox *combo;
    GError *error = NULL;
    const gchar *message = NULL;
    gchar *s = NULL;

    combo = GTK_COMBO_BOX(entry);
    args = controls->args;
    g_free(args->expression);
    args->expression = g_strdup(gtk_combo_box_get_active_text(combo));
    args->err = ARITHMETIC_OK;

    if (gwy_expr_compile(args->expr, args->expression, &error)) {
        guint nvars = gwy_expr_get_variables(args->expr, NULL);
        g_return_if_fail(nvars);
        if (nvars == 1) {
            gdouble v = gwy_expr_execute(args->expr, NULL);
            message = s = g_strdup_printf("%g", v);
            args->err = ARITHMETIC_NUMERIC;
        }
        else {
            if (gwy_expr_resolve_variables(args->expr, ARITHMETIC_NARGS,
                                           (const gchar*const*)args->name,
                                           args->pos)) {
                args->err = ARITHMETIC_EXPR;
                message = _("Expression contains unknown identifiers");
            }
        }
    }
    else {
        args->err = ARITHMETIC_EXPR;
        message = error->message;
    }

    arithmetic_show_state(controls, message);
    g_clear_error(&error);
    g_free(s);
}
