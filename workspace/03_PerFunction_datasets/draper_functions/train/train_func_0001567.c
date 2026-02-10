UnlinkBinding(Binding **pblist, Binding *b, Binding *prev)
{
	Binding *t;

	if (!prev && b != *pblist)
	{
		for (t = *pblist; t && t != b; prev = t, t = t->NextBinding)
		{

		}
		if (t == NULL)
		{

			return;
		}
	}

	if (prev)
	{

		prev->NextBinding = b->NextBinding;
	}
	else
	{

		*pblist = b->NextBinding;
	}

	return;
}
