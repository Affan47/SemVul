globus_l_stdio_ui_read(
    UI                                 *ui,
    UI_STRING                          *uis)
{
    char                                buf[100], *res;

    res = fgets(buf, sizeof(buf), stdin);

    if (res == NULL)
    {
        return 0;
    }
    if (res[strlen(res)-1] == '\n')
    {
        res[strlen(res)-1] = 0;
    }

    return UI_set_result(ui, uis, res);
}
