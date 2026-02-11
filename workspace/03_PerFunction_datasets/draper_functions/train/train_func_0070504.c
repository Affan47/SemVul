uniqueifyJsonbObject(JsonbValue *object)
{
	bool		hasNonUniq = false;

	Assert(object->type == jbvObject);

	if (object->val.object.nPairs > 1)
		qsort_arg(object->val.object.pairs, object->val.object.nPairs, sizeof(JsonbPair),
				  lengthCompareJsonbPair, &hasNonUniq);

	if (hasNonUniq)
	{
		JsonbPair  *ptr = object->val.object.pairs + 1,
				   *res = object->val.object.pairs;

		while (ptr - object->val.object.pairs < object->val.object.nPairs)
		{

			if (lengthCompareJsonbStringValue(ptr, res) != 0)
			{
				res++;
				if (ptr != res)
					memcpy(res, ptr, sizeof(JsonbPair));
			}
			ptr++;
		}

		object->val.object.nPairs = res + 1 - object->val.object.pairs;
	}
}
