picoLCD_get_key(Driver *drvthis)
{
	PrivateData *p = drvthis->private_data;
	lcd_packet keydata;
	char *keystr = NULL;
	int  keys_read = 0;
	int  key_pass  = 0;
	int  two_keys  = 0;

	debug(RPT_DEBUG, "%s: get_key start (timeout %d)",
		drvthis->name, p->key_timeout);

	while (! keys_read) {
		get_key_event(p->lcd, &keydata, p->key_timeout);
		debug(RPT_DEBUG, "%s: get_key got an event", drvthis->name);

		if (keydata.type == IN_REPORT_KEY_STATE) {
			if (! keydata.data[1] && key_pass) {
				debug(RPT_DEBUG, "%s: get_key got all clear", drvthis->name);

				keys_read++;
			}
			else if (! keydata.data[2] && ! two_keys) {
				debug(RPT_DEBUG, "%s: get_key got one key", drvthis->name);

				keystr = p->device->keymap[keydata.data[1]];
			}
			else {

				static char keybuf[2 * KEYPAD_LABEL_MAX + 1];

				debug(RPT_DEBUG, "%s: get_key got two keys", drvthis->name);
				two_keys++;
				sprintf(keybuf, "%s+%s", p->device->keymap[keydata.data[1]],
							 p->device->keymap[keydata.data[2]]);
				keystr = keybuf;
			}

			key_pass++;
		}
		else if (p->IRenabled && keydata.type == IN_REPORT_IR_DATA) {
			debug(RPT_NOTICE, "%s: get_key irdata, length=%d bytes",
				drvthis->name, keydata.data[1]);


			ir_transcode(drvthis, keydata.data + 2, keydata.data[1]);
		}
		else {
			debug(RPT_DEBUG, "%s: get_key got non-key/ir data or timeout", drvthis->name);
			if (p->result < p->resptr) {
				debug(RPT_INFO, "picolcd: timeout %d send lirc data now", p->key_timeout);

				picolcd_lircsend(drvthis);
			}

			return NULL;
		}

	}

	debug(RPT_DEBUG, "%s: get_key complete (%s)", drvthis->name, keystr);

	if ((keystr != NULL) && (strlen(keystr) > 0))
		return keystr;

	return NULL;


}
