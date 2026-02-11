soap_serialize(struct soap *soap) const
{
#ifndef WITH_NOIDREF
	if (this->__ptr && !soap_array_reference(soap, this, (struct soap_array*)&this->__ptr, 1, SOAP_TYPE_ns__List))
		for (int i = 0; i < this->__size; i++)
		{
			soap_serialize_PointerTons__Object(soap, this->__ptr + i);
		}
#endif
}
