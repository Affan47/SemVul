operator[] (unsigned int pow)
{
	mutator ();

	if (degree () < pow)
		rep->data.resize (pow + 1);
	return rep->data[pow];
}
