fx_account_tooltip(HybridAccount *account, HybridTooltipData *tip_data)
{
    fetion_account *ac;

    ac = hybrid_account_get_protocol_data(account);

    if (ac->mobileno && *ac->mobileno) {
        hybrid_tooltip_data_add_title(tip_data, ac->mobileno);

    } else {
        hybrid_tooltip_data_add_title(tip_data, ac->sid);
    }

    hybrid_tooltip_data_add_pair(tip_data, _("Name"), ac->nickname);
    hybrid_tooltip_data_add_pair(tip_data, _("Status"),
                                 hybrid_get_presence_name(account->state));

    if (ac->mobileno && *ac->mobileno) {
        hybrid_tooltip_data_add_pair(tip_data, _("Fetion Number"), ac->sid);
    } else {
        hybrid_tooltip_data_add_pair(tip_data, _("Mobile Number"),
                                     ac->mobileno);
    }
    hybrid_tooltip_data_add_pair(tip_data, _("Mood"), ac->mood_phrase);

    return TRUE;
}
