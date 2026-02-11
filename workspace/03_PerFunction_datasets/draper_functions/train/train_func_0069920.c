bufread(Buffer *b, uint q0, Rune *s, uint n)
{
	uint m;

	if(!(q0<=b->nc && q0+n<=b->nc))
		panic("bufread: internal error");

	while(n > 0){
		setcache(b, q0);
		m = min(n, b->cnc-(q0-b->cq));
		runemove(s, b->c+(q0-b->cq), m);
		q0 += m;
		s += m;
		n -= m;
	}
}
