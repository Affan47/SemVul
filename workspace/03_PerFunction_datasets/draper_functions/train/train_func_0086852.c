toast_raw_datum_size(Datum value)
{
	varattrib  *attr = (varattrib *) DatumGetPointer(value);
	Size		result;

	if (VARATT_IS_COMPRESSED(attr))
	{


		result = attr->va_content.va_compressed.va_rawsize + VARHDRSZ;
	}
	else if (VARATT_IS_EXTERNAL(attr))
	{


		result = attr->va_content.va_external.va_rawsize;
	}
	else
	{

		result = VARSIZE(attr);
	}
	return result;
}
