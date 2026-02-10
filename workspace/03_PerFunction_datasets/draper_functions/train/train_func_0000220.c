value_to_symstr(ulong value, char *buf, ulong radix)
{
        struct syment *sp;
        ulong offset;
	char *p1, locbuf[BUFSIZE];
	struct load_module *lm;

	sp = NULL;
	offset = 0;
	buf[0] = NULLCHAR;

	if (!radix)
		radix = *gdb_output_radix;
	if ((radix != 10) && (radix != 16))
		radix = 16;

        if ((sp = value_search(value, &offset))) {
                if (offset)
                        sprintf(buf, radix == 16 ? "%s+0x%lx" : "%s+%ld",
				sp->name, offset);
                else
                        sprintf(buf, "%s", sp->name);
        }

	if (module_symbol(value, NULL, NULL, locbuf, *gdb_output_radix)) {
		if (sp) {
			if (STRNEQ(locbuf, "_MODULE_START_"))
				shift_string_left(locbuf,
					strlen("_MODULE_START_"));
			if ((p1 = strstr(locbuf, "+")))
				*p1 = NULLCHAR;

			if (offset) {
				if (is_module_name(locbuf, NULL, &lm) &&
				    (value < lm->mod_text_start))
					sprintf(buf, radix == 16 ?
						"(%s module)+0x%lx" :
						"(%s module)+%ld",
						locbuf, offset);
				else
					sprintf(buf, radix == 16 ?
						"%s+0x%lx" : "%s+%ld",
						locbuf, offset);
			} else {
				if (is_module_name(locbuf, NULL, &lm) &&
				    (value < lm->mod_text_start))
					sprintf(buf, "(%s)", locbuf);
				else
					sprintf(buf, "%s", locbuf);
			}
		} else
			sprintf(buf, "%s", locbuf);
	}

        return(buf);
}
