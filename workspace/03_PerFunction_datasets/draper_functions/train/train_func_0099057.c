knh_strcaseuint64(kbytes_t t)
{
	int ch[8] = {0};
	kuint64_t n = 0;
	size_t i, c = 0;
	for(i = 0; i < 8; i++) {
		while(t.text[c] == '_') c++;
		if(c >= t.len) break;
		ch[i] = toupper(t.text[c]); c++;
	}
	if(i > 0) {
		switch(i) {
		default: n |= ((kuint64_t)ch[7]);
		case 7: n |= (((kuint64_t)ch[6]) << (64-56));
		case 6: n |= (((kuint64_t)ch[5]) << (64-48));
		case 5: n |= (((kuint64_t)ch[4]) << (64-40));
		case 4: n |= (((kuint64_t)ch[3]) << (64-32));
		case 3: n |= (((kuint64_t)ch[2]) << (64-24));
		case 2: n |= (((kuint64_t)ch[1]) << (64-16));
		case 1: n |= (((kuint64_t)ch[0]) << (64-8));
		}
	}
	return n;
}
