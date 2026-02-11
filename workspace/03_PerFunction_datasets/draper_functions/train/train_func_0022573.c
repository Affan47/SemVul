xl_xml_num_fmt (GsfXMLIn *xin, xmlChar const **attrs)
{
	static struct {
		char const *name;
		GOFormatMagic id;
	} named_magic_formats [] = {
		{ "General Date",        GO_FORMAT_MAGIC_SHORT_DATETIME },
		{ "Long Date",           GO_FORMAT_MAGIC_LONG_DATE },
		{ "Medium Date",         GO_FORMAT_MAGIC_MEDIUM_DATE },
		{ "Short Date",          GO_FORMAT_MAGIC_SHORT_DATE },
		{ "Long Time",           GO_FORMAT_MAGIC_LONG_TIME },
		{ "Medium Time",         GO_FORMAT_MAGIC_MEDIUM_TIME },
		{ "Short Time",          GO_FORMAT_MAGIC_SHORT_TIME },
		{ NULL, 0 }
	};
	static struct {
		char const *name;
		char const *format;
	} named_formats [] = {
		{ "General Number",     "General" },
		{ "Currency",       	"$#,##0.00_);[Red](#,##0.00)" },
		{ "Euro Currency",     	"[$EUR-2]#,##0.00_);[Red](#,##0.00)" },
		{ "Fixed",              "0.00" },
		{ "Standard",           "#,##0.00" },
		{ "Percent",            "0.00%" },
		{ "Scientific",         "0.00E+00" },
		{ "Yes/No",		"\"Yes\";\"Yes\";\"No\"" },
		{ "True/False",		"\"True\";\"True\";\"False\"" },
		{ "On/Off",		"\"On\";\"On\";\"Off\"" },
		{ NULL, NULL }
	};
	ExcelXMLReadState *state = (ExcelXMLReadState *)xin->user_state;
	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, attrs[0], XL_NS_SS, "Format")) {
			GOFormat *fmt = NULL;
			int i;

			for (i = 0 ; named_formats[i].name ; i++)
				if (0 == strcmp (attrs[1], named_formats[i].name))
					fmt = go_format_new_from_XL (named_formats[i].format);

			if (NULL == fmt)
				for (i = 0 ; named_magic_formats[i].name ; i++)
					if (0 == strcmp (attrs[1], named_magic_formats[i].name))
						fmt = go_format_new_magic (named_magic_formats[i].id);

			if (NULL == fmt)
				fmt = go_format_new_from_XL (attrs[1]);
			gnm_style_set_format (state->style, fmt);
			go_format_unref (fmt);
		} else
			unknown_attr (xin, attrs, "Style::NumberFormat");
}
