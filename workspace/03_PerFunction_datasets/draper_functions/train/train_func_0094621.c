operator== ( const Type& t1, const Type& t2)
{
	SimpleType 	*st1, *st2;
	TableType	*tt1, *tt2;
	TupletType	*nt1, *nt2;

	if (t1->variability() != t2->variability()) 	return false;
	if (t1->computability() != t2->computability()) return false;

    if ( (st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2)) )
        return     (st1->nature() == st2->nature())
                && (st1->variability() == st2->variability())
                && (st1->computability() == st2->computability())
                && (st1->vectorability() == st2->vectorability())
                && (st1->boolean() == st2->boolean())
                && (st1->getInterval().lo == st2->getInterval().lo)
                && (st1->getInterval().hi == st2->getInterval().hi)
                && (st1->getInterval().valid == st2->getInterval().valid);
    if ( (tt1 = isTableType(t1)) && (tt2 = isTableType(t2)) )
        return tt1->content()== tt2->content();
	if ( (nt1 = isTupletType(t1)) && (nt2 = isTupletType(t2)) ) {
		int a1 = nt1->arity();
		int a2 = nt2->arity();
		if (a1 == a2) {
			for (int i=0; i<a1; i++)  { if ((*nt1)[i] != (*nt2)[i]) return false; }
			return true;
		} else {
			return false;
		}
	}
	return false;
}
