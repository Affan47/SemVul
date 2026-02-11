uint160_strdup_printf (const UInt160 *var)
{

	GString *string = g_string_new("");
	guint64 val;
	gsize size = 0;
	guchar * pointer;
	int i;


	if (var->value2 != 0) {
		size = 16;
		val = var->value2;
		while (val != 0) {
			val = val >> 8;
			size++;
		}
	} else if (var->value1 != 0) {
		size = 8;
		val = var->value1;
		while (val != 0) {
			val = val >> 8;
			size ++;
		}
	} else if (var->value0 != 0) {
		val = var->value0;
		while (val != 0) {
			val = val >> 8;
			size ++;
		}
	}

	for (i=size-1; i>=0; i--) {
		if (i < 8) {
			pointer = (guchar *) &(var->value0);
			g_string_append_printf (string, "%s%02X", (i==(size-1)?"":":"), pointer[i]);
		} else if (i < 16) {
			pointer = (guchar *) &(var->value1);
			g_string_append_printf (string, "%s%02X", (i==(size-1)?"":":"), pointer[i-8]);
		} else {
                                pointer = (guchar *) &(var->value2);
                                g_string_append_printf (string, "%s%02X", (i==(size-1)?"":":"), pointer[i-16]);
		}
	}

	return g_string_free (string, FALSE);

}
