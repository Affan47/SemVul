fail(string message)
{
	mail::callback *c=callback;

	callback=NULL;

	delete this;
	c->fail(message);
}
