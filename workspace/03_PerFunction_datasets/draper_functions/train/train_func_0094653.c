fmt_dict(struct fmt *fmt, pdf_obj *obj)
{
	int i, n;
	pdf_obj *key, *val;

	n = pdf_dict_len(obj);
	if (fmt->tight) {
		fmt_puts(fmt, "<<");
		for (i = 0; i < n; i++) {
			fmt_obj(fmt, pdf_dict_get_key(obj, i));
			fmt_sep(fmt);
			fmt_obj(fmt, pdf_dict_get_val(obj, i));
			fmt_sep(fmt);
		}
		fmt_puts(fmt, ">>");
	}
	else {
		fmt_puts(fmt, "<<\n");
		fmt->indent ++;
		for (i = 0; i < n; i++) {
			key = pdf_dict_get_key(obj, i);
			val = pdf_dict_get_val(obj, i);
			fmt_indent(fmt);
			fmt_obj(fmt, key);
			fmt_putc(fmt, ' ');
			if (!pdf_is_indirect(val) && pdf_is_array(val))
				fmt->indent ++;
			fmt_obj(fmt, val);
			fmt_putc(fmt, '\n');
			if (!pdf_is_indirect(val) && pdf_is_array(val))
				fmt->indent --;
		}
		fmt->indent --;
		fmt_indent(fmt);
		fmt_puts(fmt, ">>");
	}
}
