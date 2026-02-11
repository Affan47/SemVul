dsgw_emit_confirm_script()
{
    char *yes_key_str = dsgw_get_cgi_var("YES", DSGW_CGIVAR_OPTIONAL);

    int yes_key;
    char *yes = NULL, *no = NULL;

    if (!yes_key_str) {
	yes_key = 0;
    } else if (!strcasecmp(yes_key_str, "CONFIRMVALUE1")) {
	yes_key = DBT_confirmValue1;
    } else if (!strcasecmp(yes_key_str, "CONFIRMVALUE2")) {
	yes_key = DBT_confirmValue2;
    } else if (!strcasecmp(yes_key_str, "CONFIRMVALUE3")) {
	yes_key = DBT_confirmValue3;
    } else if (!strcasecmp(yes_key_str, "CONFIRMVALUE4")) {
	yes_key = DBT_confirmValue4;
    } else if (!strcasecmp(yes_key_str, "CONFIRMVALUE5")) {
	yes_key = DBT_confirmValue5;
    }

    yes = XP_GetClientStr(yes_key);

    dsgw_emitf ("<SCRIPT type=\"text/javascript\"><!--\n"
		"function OK() {\n");
    if (yes) dsgw_emitf ("    %s\n", yes);
    dsgw_emits ("    top.close();\n"
		"}\n"
		"\n"
		"function Cancel() {\n");
    if (no) dsgw_emitf ("    %s\n", no);
    dsgw_emits ("    top.close();\n"
		"}\n"
		"// -->\n"
		"</SCRIPT>\n");

    return;
}
