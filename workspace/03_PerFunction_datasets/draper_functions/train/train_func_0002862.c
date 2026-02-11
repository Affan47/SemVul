xkeyboard_symParse(gchar *symbols, gint count)
{
	START_FUNC
	GList *ret=NULL;
	gboolean inSymbol=FALSE;
	gchar curSymbol[32];
	guint i;
	gchar ch;
	gint c=0;

	curSymbol[0]='\0';
	for (i=0 ; i<strlen(symbols) ; i++) {
		ch=symbols[i];
		if (ch=='+') {
			if (inSymbol) {
				if (xkeyboard_is_sym(curSymbol)) {
					xkeyboard_list_append(curSymbol, &ret);
					c++; if (c>=count) break;
				}
				curSymbol[0]='\0';
			} else inSymbol=TRUE;
		} else if (inSymbol && (ISALPHA(ch) || ch=='_')) {
			if (strlen(curSymbol)<31) {
				curSymbol[strlen(curSymbol)+1]='\0';
				curSymbol[strlen(curSymbol)]=ch;
			}
		} else if (inSymbol) {
			if (xkeyboard_is_sym(curSymbol))
				xkeyboard_list_append(curSymbol, &ret);
				c++; if (c>=count) break;
			curSymbol[0]='\0';
			inSymbol=FALSE;
		}
	}

	if (inSymbol && curSymbol[0] && xkeyboard_is_sym(curSymbol) && (c<count))
		xkeyboard_list_append(curSymbol, &ret);

	END_FUNC
	return ret;
}
