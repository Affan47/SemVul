classmatch(int classno, int c, int negate)
{
	Rune *p;

	p = class[classno];
	while(*p){
		if(*p == Runemax){
			if(p[1]<=c && c<=p[2])
				return !negate;
			p += 3;
		}else if(*p++ == c)
			return !negate;
	}
	return negate;
}
