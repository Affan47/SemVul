change(Provider::Context *c)
{
	if(c)
		d = new Private(c);
	else
		d = 0;
}
