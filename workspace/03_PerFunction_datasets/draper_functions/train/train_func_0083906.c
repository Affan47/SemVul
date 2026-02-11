code_first(U16B cp, S16B c) {

    register U16B i;
    register S16B sum,cf,tot,esc;

    sum=cf=0;
    for (i=cp;i!=NIL;i=nb[i]) {
	if (fc[i]==c) {
	    cf=fa[i];
	    as[0]=i;
	    break;
	}
	sum+=fa[i];
    }
    tot=ft[cp];
    esc=adj_escape_prob(fe[cp],cp);
    if (nec>=NECLIM) {
	if (tot<=NECTLIM && nec==NECMAX) {
	    tot<<=2;
	    sum<<=2;
	    cf<<=2;
	}
	else {
	    tot<<=1;
	    sum<<=1;
	    cf<<=1;
	}
    }
    usp=1;
    if (cf==0) {
	ac_out(tot,tot+esc,tot+esc);
	for (i=cp;i!=NIL;sum=i,i=nb[i]) {
	    cmstack[cmsp++]=fc[i];
	    cmask[fc[i]]=1;
	}
	as[0]=sum;
	nec=0;
	if (ft[cp]==1 && iec[cl[cp]]<IECLIM) ++iec[cl[cp]];
	cps[0]=0x8000|cp;
	return 0;
    }
    ac_out(sum,sum+cf,tot+esc);
    if (nec<NECMAX) ++nec;
    if (ft[cp]==1 && iec[cl[cp]]) --iec[cl[cp]];
    cps[0]=cp;
    return 1;
}
