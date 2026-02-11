Raise_CompareError(const SQObject &o1, const SQObject &o2)
{
	SQObjectPtr oval1 = PrintObjVal(o1), oval2 = PrintObjVal(o2);
	Raise_Error(_SC("comparsion between '%.50s' and '%.50s'"), _stringval(oval1), _stringval(oval2));
}
