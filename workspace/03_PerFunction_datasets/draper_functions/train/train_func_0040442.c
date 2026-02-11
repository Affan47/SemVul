buy_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
  char tbuf[512], buf[512];
  struct city_dialog *pdialog = (struct city_dialog *)client_data;;
  const char *name = city_production_name_translation(pdialog->pcity);
  int value = city_production_buy_gold_cost(pdialog->pcity);

  if (!can_client_issue_orders()) {
    return;
  }

  fc_snprintf(tbuf, ARRAY_SIZE(tbuf), PL_("Treasury contains %d gold.",
                                          "Treasury contains %d gold.",
                                          client_player()->economic.gold),
              client_player()->economic.gold);

  if (value <= client_player()->economic.gold) {
    fc_snprintf(buf, sizeof(buf),

                PL_("Buy %s for %d gold?\n%s",
                    "Buy %s for %d gold?\n%s", value),
                name, value, tbuf);
    popup_message_dialog(pdialog->shell, "buydialog", buf,
			 buy_callback_yes, pdialog, 0,
			 buy_callback_no, 0, 0,
			 NULL);
  }
  else {
    fc_snprintf(buf, sizeof(buf),

                PL_("%s costs %d gold.\n%s",
                    "%s costs %d gold.\n%s", value),
                name, value, tbuf);
    popup_message_dialog(pdialog->shell, "buynodialog", buf,
			 buy_callback_no, 0, 0,
			 NULL);
  }

}
