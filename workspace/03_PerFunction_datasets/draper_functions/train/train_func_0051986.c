GetText(struct XObj *xobj, int End)
{
	char *str;
	int a,b;

	if (End > xobj->value)
	{
		a = getByteOffsetBoundsCheck(xobj->Ffont, xobj->title,
					     xobj->value);
		b = getByteOffsetBoundsCheck(xobj->Ffont, xobj->title,
					     End);
	}
	else
	{
		b = getByteOffsetBoundsCheck(xobj->Ffont, xobj->title,
					     xobj->value);
		a = getByteOffsetBoundsCheck(xobj->Ffont, xobj->title,
					     End);
	}
	str = (char*)calloc(b-a+2,1);
	memcpy(str, &xobj->title[a], b-a);
	str[b-a+1] = '\0';
	return str;
}
