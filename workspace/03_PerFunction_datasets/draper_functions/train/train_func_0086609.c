getTriggerKeys(w)
Widget w;
{
    IMProtocolWidget ipw = (IMProtocolWidget)w;
    char *key_str;
    IMTriggerKey keys[100];
    int num_keys;
    int c, n;
    ICTriggerKey *ckeys, *ekeys;

    TRACE(("IMProtocolWidget:getTriggerKeys()\n"));

    key_str = ipw->imp.conversion_start_keys;
    num_keys = 0;
    TRACE(("\tstart keys: %s\n", key_str));

    if (key_str != NULL) {
	do {
	    char buf[256];
	    char *p = buf;
	    KeySym keysym;
	    long mods, chk_mods;

	    while ((c = *key_str++) != '\0' && c != '\n') {
		*p++ = c;
	    }
	    *p = '\0';
	    if (ParseKeyEvent(buf, &keysym, &mods, &chk_mods)) {
		TRACE(("\tkeysym: %08lx, modifiers: %04lx, check: %04lx\n",
		       keysym, mods, chk_mods));
		keys[num_keys].keysym = keysym;
		keys[num_keys].modifiers = mods;
		keys[num_keys].check_modifiers = chk_mods;
		num_keys++;
	    }
	} while  (c != '\0' && num_keys < 100);
    }

    n = ICGetTriggerKeysOfInputObjectClass(ipw->imp.input_object_class,
					   &ckeys);
    for (ekeys = ckeys + n ;
	 ckeys < ekeys && num_keys < (sizeof(keys) / sizeof(IMTriggerKey)) ;
	 ckeys++) {
      keys[num_keys].keysym = ckeys->keysym;
      keys[num_keys].modifiers = ckeys->modifiers;
      keys[num_keys].check_modifiers = ckeys->modifiermask;
      num_keys++;
    }

    TRACE(("\tnumber of trigger keys: %d\n", num_keys));
    ipw->imp.num_trigger_keys = num_keys;

    if (num_keys > 0) {
	int size;

	size = sizeof(IMTriggerKey) * num_keys;
	ipw->imp.trigger_keys = (IMTriggerKey *)XtMalloc(size);
	bcopy((char *)keys, (char *)ipw->imp.trigger_keys, size);
    } else {
	ipw->imp.trigger_keys = NULL;
    }
}
