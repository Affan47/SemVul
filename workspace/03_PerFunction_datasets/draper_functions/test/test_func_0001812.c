IoCFunction_print(IoCFunction *self)
{
	IoCFunctionData *data = DATA(self);

	printf("CFunction_%p", self);
	printf(" %p", (data->func));
	printf(" %s", data->typeTag ? data->typeTag->name : "?");
	if (data->uniqueName) printf(" %s", CSTRING(data->uniqueName));
	printf("\n");
}
