setWidth(int w)
{
	if (w > 0)
	{
		width=w;


		vector<AddressField *>::iterator b, e;

		b=fields.begin();
		e=fields.end();

		while (b != e)
		{
			AddressField *f= *b++;

			if (f)
				f->setWidth(w);
		}
	}
}
