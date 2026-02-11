toast_datum_size(Datum value)
{
	struct varlena *attr = (struct varlena *) DatumGetPointer(value);
	Size		result;

	if (VARATT_IS_EXTERNAL(attr))
	{


		struct varatt_external toast_pointer;

		VARATT_EXTERNAL_GET_POINTER(toast_pointer, attr);
		result = toast_pointer.va_extsize;
	}
	else if (VARATT_IS_SHORT(attr))
	{
		result = VARSIZE_SHORT(attr);
	}
	else
	{


		result = VARSIZE(attr);
	}
	return result;
}
