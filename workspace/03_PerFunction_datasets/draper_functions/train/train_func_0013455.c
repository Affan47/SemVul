overlay_key_down(void *data __UNUSED__,
		 int type __UNUSED__,
		 void *event)
{
    Ecore_Event_Key *ev = event;
    Border_Extra *extra;

    if (ev->event_window != _G.action_input_win)
        return ECORE_CALLBACK_PASS_ON;

    if (strcmp(ev->key, "Return") == 0)
        goto stop;
    if (strcmp(ev->key, "Escape") == 0)
        goto stop;
    if (strcmp(ev->key, "Backspace") == 0) {
        char *key = _G.keys;

        while (*key)
            key++;
        *key = '\0';
        return ECORE_CALLBACK_RENEW;
    }

    if (ev->key[0] && !ev->key[1] && strchr(tiling_g.config->keyhints,
                                            ev->key[1])) {
        char *key = _G.keys;

        while (*key)
            key++;
        *key++ = ev->key[0];
        *key = '\0';

        extra = eina_hash_find(_G.overlays, _G.keys);
        if (extra) {
            _G.action_cb(_G.focused_bd, extra);
        } else {
            return ECORE_CALLBACK_RENEW;
        }
    }

stop:
    end_special_input();
    return ECORE_CALLBACK_DONE;
}
