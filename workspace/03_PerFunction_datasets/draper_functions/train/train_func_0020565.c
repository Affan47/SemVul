matchIdSubst(LexemeInfo *stored, uint32 idsubst)
{
	bool		res = true;

	if (stored)
	{
		res = false;

		for (; stored; stored = stored->nextvariant)
			if (stored->idsubst == idsubst)
			{
				res = true;
				break;
			}
	}

	return res;
}
