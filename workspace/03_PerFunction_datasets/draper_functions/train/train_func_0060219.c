IoEvOutResponse_free(IoEvOutResponse *self)
{
	if (REQUEST(self))
	{

		IoObject_setDataPointer_(self, 0x0);
	}
}
