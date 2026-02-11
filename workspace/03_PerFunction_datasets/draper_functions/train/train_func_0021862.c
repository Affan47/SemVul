col_to_json(MYSQL_FIELD field, char * val, apr_pool_t *mpool) {
	json_value * ret= NULL;
	if ( !val) {
		return json_create_null(mpool);
	}
	switch (field.type) {
	case MYSQL_TYPE_TINY:
	case MYSQL_TYPE_SHORT:
	case MYSQL_TYPE_LONG:
	case MYSQL_TYPE_INT24:
		ret = json_create_long(mpool, atol(val));
		break;
	case MYSQL_TYPE_DECIMAL:
	case MYSQL_TYPE_NEWDECIMAL:
	case MYSQL_TYPE_DOUBLE:
	case MYSQL_TYPE_FLOAT:
	case MYSQL_TYPE_LONGLONG:
		ret = json_create_double(mpool, atof(val));
		break;
	case MYSQL_TYPE_BIT:
	case MYSQL_TYPE_TIMESTAMP:
	case MYSQL_TYPE_DATE:
	case MYSQL_TYPE_TIME:
	case MYSQL_TYPE_DATETIME:
	case MYSQL_TYPE_YEAR:
	case MYSQL_TYPE_STRING:
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_NEWDATE:
	case MYSQL_TYPE_VARCHAR:
		ret = json_create_string(mpool, val);
		break;
	case MYSQL_TYPE_BLOB:
	case MYSQL_TYPE_TINY_BLOB:
	case MYSQL_TYPE_MEDIUM_BLOB:
	case MYSQL_TYPE_LONG_BLOB:


		if (field.charsetnr == 63) {

			ret = json_create_null(mpool);
		} else {
			ret = json_create_string(mpool, val);
		}
		break;
	case MYSQL_TYPE_SET:
	case MYSQL_TYPE_ENUM:
	case MYSQL_TYPE_GEOMETRY:
	case MYSQL_TYPE_NULL:
		ret = json_create_null(mpool);
		break;
	}
	return ret;
}
