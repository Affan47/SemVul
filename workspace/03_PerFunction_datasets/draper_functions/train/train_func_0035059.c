testCompare()
{
	File f1("abc.txt");
	File f2("def.txt");
	File f3("abc.txt");

	assert (f1 == f3);
	assert (!(f1 == f2));
	assert (f1 != f2);
	assert (!(f1 != f3));
	assert (!(f1 == f2));
	assert (f1 < f2);
	assert (f1 <= f2);
	assert (!(f2 < f1));
	assert (!(f2 <= f1));
	assert (f2 > f1);
	assert (f2 >= f1);
	assert (!(f1 > f2));
	assert (!(f1 >= f2));

	assert (f1 <= f3);
	assert (f1 >= f3);
}
