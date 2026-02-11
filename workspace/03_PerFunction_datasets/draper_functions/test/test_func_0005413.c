opal_ifindextomac(int if_index, uint8_t mac[6])
{
    opal_if_t* intf;

    for (intf = (opal_if_t*)opal_list_get_first(&opal_if_list);
        intf != (opal_if_t*)opal_list_get_end(&opal_if_list);
        intf = (opal_if_t*)opal_list_get_next(intf)) {
        if (intf->if_index == if_index) {
            memcpy(mac, &intf->if_mac, 6);
            return OPAL_SUCCESS;
        }
    }
    return OPAL_ERROR;
}
