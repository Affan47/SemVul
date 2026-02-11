soap_serialize_ArrayOfstring(struct soap *soap, struct ArrayOfstring const*a)
{
#ifndef WITH_NOIDREF
	int i;
	if (a->__ptritem && !soap_array_reference(soap, a, (struct soap_array*)&a->__ptritem, 1, SOAP_TYPE_ArrayOfstring))
		for (i = 0; i < a->__size; i++)
		{
			soap_serialize_string(soap, a->__ptritem + i);
		}
#endif
}
