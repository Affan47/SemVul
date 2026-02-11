registerType(awt_item_type type, AW_window_menu_modes *awm, AWT_OpenMaskWindowCallback open_window_cb) {
    map<awt_item_type, AWT_registered_itemtype>::const_iterator alreadyRegistered = registeredTypes.find(type);
    if (alreadyRegistered == registeredTypes.end()) {
        registeredTypes[type] = AWT_registered_itemtype(awm, open_window_cb);
    }
#if defined(DEBUG)
    else {

        awt_assert(alreadyRegistered->second.getOpenCb() == open_window_cb);
    }
#endif
}
