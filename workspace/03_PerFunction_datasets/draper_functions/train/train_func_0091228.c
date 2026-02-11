makeRecSchema (schema* s1, schema* s2)
{
	schema*	a = makeEnlargedSchema(s1, s2->width());
	schema*	b = makeEnlargedSchema(s2, s1->width());
	double 	m = dWire * max(b->inputs(), b->outputs());
	double 	w = a->width() + 2*m;

	return new recSchema(a,b,w);
}
