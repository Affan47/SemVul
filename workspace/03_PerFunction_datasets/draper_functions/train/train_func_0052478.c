at2_destroy_modem(ModemDef *modem)
{
    if (modem != NULL) {
        O_DESTROY(modem->id);
        O_DESTROY(modem->name);
        O_DESTROY(modem->detect_string);
        O_DESTROY(modem->detect_string2);
        O_DESTROY(modem->init_string);
        O_DESTROY(modem->enable_hwhs);
        O_DESTROY(modem->keepalive_cmd);
        O_DESTROY(modem->message_storage);
        O_DESTROY(modem->reset_string);
        gw_free(modem);
    }
}
