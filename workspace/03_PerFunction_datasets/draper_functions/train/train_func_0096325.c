retrive_param_values(param_array *Param)
{
    switch(Param->type.c) {
    case SQL_C_CHAR:
    case SQL_C_WCHAR:
    case SQL_C_TYPE_TIMESTAMP:
        return (void *)Param->values.string;
    case SQL_C_SLONG:
	return (void *)Param->values.integer;
    case SQL_C_DOUBLE:
	return (void *)Param->values.floating;
    case SQL_C_BIT:
	return (void *)Param->values.bool;
    default:
	DO_EXIT(EXIT_FAILURE);
    }
}
