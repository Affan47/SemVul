bytes_parsemn(CTX ctx, kbytes_t t)
{
	if(t.utext[0] == '%' && t.utext[1] != '%') {
		size_t i;
		for(i = 1; i < t.len; i++) {
			int ch = t.utext[i];
			if(isalnum(ch) || ch == ':' || ch == ' ') continue;
			if(ch == '.' && !isalpha(t.utext[i-1])) continue;
			break;
		}
		if(i == t.len) {
			return knh_getmn(ctx, t, MN_NEWID);
		}
	}
	return MN__s;
}
