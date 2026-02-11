get_affinity (const gchar *type)
{
	guint32 h = 0;
	gint aff = SQLITE_TEXT;
	const unsigned char *ptr = (unsigned char *) type;

	while( *ptr ){
		h = (h<<8) + g_ascii_tolower(*ptr);
		ptr++;
		if( h==(('c'<<24)+('h'<<16)+('a'<<8)+'r') ){
			aff = SQLITE_TEXT;
		}else if( h==(('c'<<24)+('l'<<16)+('o'<<8)+'b') ){
			aff = SQLITE_TEXT;
		}else if( h==(('t'<<24)+('e'<<16)+('x'<<8)+'t') ){
			aff = SQLITE_TEXT;
		}else if( h==(('b'<<24)+('l'<<16)+('o'<<8)+'b')
			  && (aff==SQLITE_INTEGER || aff==SQLITE_FLOAT) ){
			aff = 0;
		}else if( h==(('r'<<24)+('e'<<16)+('a'<<8)+'l')
			  && aff==SQLITE_INTEGER ){
			aff = SQLITE_FLOAT;
		}else if( h==(('f'<<24)+('l'<<16)+('o'<<8)+'a')
			  && aff==SQLITE_INTEGER ){
			aff = SQLITE_FLOAT;
		}else if( h==(('d'<<24)+('o'<<16)+('u'<<8)+'b')
			  && aff==SQLITE_INTEGER ){
			aff = SQLITE_FLOAT;
		}else if( (h&0x00FFFFFF)==(('i'<<16)+('n'<<8)+'t') ){
			aff = SQLITE_INTEGER;
			break;
		}
	}

	return aff;
}
