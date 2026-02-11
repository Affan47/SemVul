SetupWindow(void)
{
    txt_window_t *window;
    txt_table_t *table;
    txt_table_t *rightpane;
    txt_checkbox_t *cheesy_checkbox;
    txt_window_action_t *pwn;
    txt_label_t *toplabel;
    char buf[100];
    int i;

    window = TXT_NewWindow("Window test");

    TXT_AddWidget(window, TXT_NewSeparator("Main section"));
    table = TXT_NewTable(3);

    toplabel = TXT_NewLabel("This is a multiline label.\n"
                            "A single label object contains \n"
                            "all three of these lines.\n");
    TXT_AddWidget(window, toplabel);
    TXT_SetWidgetAlign(toplabel, TXT_HORIZ_CENTER);


    TXT_AddWidget(window, table);

    for (i=0; i<5; ++i)
    {
        sprintf(buf, "Option %i in a table:", i + 1);
        TXT_AddWidget(table, TXT_NewLabel(buf));
        sprintf(buf, " Button %i-1 ", i + 1);
        TXT_AddWidget(table, TXT_NewButton(buf));
        sprintf(buf, " Button %i-2 ", i + 1);
        TXT_AddWidget(table, TXT_NewButton(buf));
    }

    TXT_AddWidget(window, TXT_NewStrut(0, 1));
    value_label = TXT_NewLabel("");
    TXT_AddWidget(window, value_label);

    table = TXT_NewTable(2);
    TXT_AddWidget(window, table);
    TXT_SetWidgetAlign(table, TXT_HORIZ_CENTER);

    cheesy_checkbox = TXT_NewCheckBox("Cheesy", &cheesy);
    TXT_AddWidget(table, cheesy_checkbox);
    TXT_SignalConnect(cheesy_checkbox, "changed", UpdateLabel, NULL);

    rightpane = TXT_NewTable(1);
    TXT_AddWidget(table, rightpane);

    for (i=0; i<3; ++i)
    {
        txt_radiobutton_t *rbut;

        rbut = TXT_NewRadioButton(radio_values[i], &radiobutton_value, i);
        TXT_AddWidget(rightpane, rbut);
        TXT_SignalConnect(rbut, "selected", UpdateLabel, NULL);
    }

    UpdateLabel(NULL, NULL);

    TXT_AddWidget(window, TXT_NewButton2("Close Window", CloseWindow, NULL));

    pwn = TXT_NewWindowAction(KEY_F1, "PWN!");
    TXT_SetWindowAction(window, TXT_HORIZ_CENTER, pwn);
    TXT_SignalConnect(pwn, "pressed", PwnBox, NULL);

    firstwin = window;
}
