operator* 	(const Type& t1, const Type& t2)
{
	vector<Type>	v;

	TupletType* nt1 = dynamic_cast<TupletType*>((AudioType*)t1);
	TupletType* nt2 = dynamic_cast<TupletType*>((AudioType*)t2);

	if (nt1) {
		for (int i=0; i<nt1->arity(); i++) {
			v.push_back((*nt1)[i]);
		}
	} else {
		v.push_back(t1);
	}

	if (nt2) {
		for (int i=0; i<nt2->arity(); i++) {
			v.push_back((*nt2)[i]);
		}
	} else {
		v.push_back(t2);
	}
	return new TupletType(v);
}
