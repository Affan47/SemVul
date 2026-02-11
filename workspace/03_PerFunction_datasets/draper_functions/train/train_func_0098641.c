rcut(List *r, Posn p1, Posn p2)
{
	Posn p, x;
	int i;

	if(p1 == p2)
		panic("rcut 0");
	for(p=0,i=0; i<r->nused && p+L(i)<=p1; p+=L(i++))
		;
	if(i == r->nused)
		panic("rcut 1");
	if(p < p1){
		if(p+L(i) < p2){
			x = p1-p;
			p += L(i);
		}else{
			x = L(i)-(p2-p1);
			p = p2;
		}
		if(T(i))
			P(i) = x|M;
		else
			P(i) = x;
		i++;
	}
	while(i<r->nused && p+L(i)<=p2){
		p += L(i);
		dellist(r, i);
	}
	if(p < p2){
		if(i == r->nused)
			panic("rcut 2");
		x = L(i)-(p2-p);
		if(T(i))
			P(i) = x|M;
		else
			P(i) = x;
	}

	if(i>0 && i<r->nused && T(i-1)==T(i)){
		x = L(i-1)+L(i);
		dellist(r, i--);
		if(T(i))
			P(i)=x|M;
		else
			P(i)=x;
	}
}
