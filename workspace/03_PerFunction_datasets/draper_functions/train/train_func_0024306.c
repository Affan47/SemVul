sigCartesianProd (Tree s1, Tree s2)
{
	Tree 	l1, l2;
	int		m1, m2;

	if (isSigTuple(s1, &m1, l1) && (m1 == 0)) {

	} else {
		l1 = list1(s1);
	}

	if (isSigTuple(s2, &m2, l2) && (m2 == 0)) {

	} else {
		l2 = list1(s2);
	}


	return sigTuple(0, concat(l1,l2));
}
