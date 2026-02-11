THX_parse_sqstring(pTHX_ U8 *end, U8 **pp)
{
	U8 *p = *pp;
	SV *datum = sv_2mortal(newSVpvs(""));
	SvUTF8_on(datum);
	while(1) {
		U8 c = *p;
		if(p == end || char_is_control(c)) throw_syntax_error(p);
		if(c == '\'') break;
		if(c != '\\') {
			U8 *q = p;
			do {
				U32 val = char_unicode(q);
				if(unichar_is_control(val))
					throw_syntax_error(q);
				q += UTF8SKIP(q);
				c = *q;
			} while(q != end && c != '\'' && c != '\\');
			sv_catpvn_nomg(datum, (char*)p, q-p);
			p = q;
		} else {
			c = p[1];
			if(c == '\\' || c == '\'')
				p++;
			sv_catpvn_nomg(datum, (char*)p, 1);
			p++;
		}
	}
	*pp = p+1;
	return datum;
}
