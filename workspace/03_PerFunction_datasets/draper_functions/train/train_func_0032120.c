setFindString(const UT_UCSChar * string)
{
	UT_UCSChar *findString = getFvView()->findGetFindString();
	if (string && findString && UT_UCS4_strcmp(string, findString) != 0)
	{


		getFvView()->cmdUnselectSelection();
	}
	FREEP(findString);

	getFvView()->findSetFindString(string);
}
