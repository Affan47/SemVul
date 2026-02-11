jsonb_categorize_type(Oid typoid,
					  JsonbTypeCategory *tcategory,
					  Oid *outfuncoid)
{
	bool		typisvarlena;


	typoid = getBaseType(typoid);

	*outfuncoid = InvalidOid;


	switch (typoid)
	{
		case BOOLOID:
			*tcategory = JSONBTYPE_BOOL;
			break;

		case INT2OID:
		case INT4OID:
		case INT8OID:
		case FLOAT4OID:
		case FLOAT8OID:
		case NUMERICOID:
			getTypeOutputInfo(typoid, outfuncoid, &typisvarlena);
			*tcategory = JSONBTYPE_NUMERIC;
			break;

		case DATEOID:
			*tcategory = JSONBTYPE_DATE;
			break;

		case TIMESTAMPOID:
			*tcategory = JSONBTYPE_TIMESTAMP;
			break;

		case TIMESTAMPTZOID:
			*tcategory = JSONBTYPE_TIMESTAMPTZ;
			break;

		case JSONBOID:
			*tcategory = JSONBTYPE_JSONB;
			break;

		case JSONOID:
			*tcategory = JSONBTYPE_JSON;
			break;

		default:

			if (OidIsValid(get_element_type(typoid)))
				*tcategory = JSONBTYPE_ARRAY;
			else if (type_is_rowtype(typoid))
				*tcategory = JSONBTYPE_COMPOSITE;
			else
			{

				*tcategory = JSONBTYPE_OTHER;


				if (typoid >= FirstNormalObjectId)
				{
					Oid			castfunc;
					CoercionPathType ctype;

					ctype = find_coercion_pathway(JSONOID, typoid,
											   COERCION_EXPLICIT, &castfunc);
					if (ctype == COERCION_PATH_FUNC && OidIsValid(castfunc))
					{
						*tcategory = JSONBTYPE_JSONCAST;
						*outfuncoid = castfunc;
					}
					else
					{

						getTypeOutputInfo(typoid, outfuncoid, &typisvarlena);
					}
				}
				else
				{

					getTypeOutputInfo(typoid, outfuncoid, &typisvarlena);
				}
				break;
			}
	}
}
