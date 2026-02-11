prodInRange(line,pats,ls,us,is)
Int  line;
List pats;
Cell ls, us, is; {


    Cell e = ap2(nameInRange,ap2(mkTuple(2),arg(ls),arg(us)),arg(is));
    while (ls=fun(ls), us=fun(us), is=fun(is), isAp(ls)) {
	e = ap2(nameAnd,
		ap2(nameInRange,ap2(mkTuple(2),arg(ls),arg(us)),arg(is)),
		e);
    }
    e = singleton(pair(pats,pair(mkInt(line),e)));
    return mkBind("inRange",e);
}
