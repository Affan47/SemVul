php_dom_throw_error(int error_code, int strict_error TSRMLS_DC)
{
	char *error_message;

	switch (error_code)
	{
		case INDEX_SIZE_ERR:
			error_message = "Index Size Error";
			break;
		case DOMSTRING_SIZE_ERR:
			error_message = "DOM String Size Error";
			break;
		case HIERARCHY_REQUEST_ERR:
			error_message = "Hierarchy Request Error";
			break;
		case WRONG_DOCUMENT_ERR:
			error_message = "Wrong Document Error";
			break;
		case INVALID_CHARACTER_ERR:
			error_message = "Invalid Character Error";
			break;
		case NO_DATA_ALLOWED_ERR:
			error_message = "No Data Allowed Error";
			break;
		case NO_MODIFICATION_ALLOWED_ERR:
			error_message = "No Modification Allowed Error";
			break;
		case NOT_FOUND_ERR:
			error_message = "Not Found Error";
			break;
		case NOT_SUPPORTED_ERR:
			error_message = "Not Supported Error";
			break;
		case INUSE_ATTRIBUTE_ERR:
			error_message = "Inuse Attribute Error";
			break;
		case INVALID_STATE_ERR:
			error_message = "Invalid State Error";
			break;
		case SYNTAX_ERR:
			error_message = "Syntax Error";
			break;
		case INVALID_MODIFICATION_ERR:
			error_message = "Invalid Modification Error";
			break;
		case NAMESPACE_ERR:
			error_message = "Namespace Error";
			break;
		case INVALID_ACCESS_ERR:
			error_message = "Invalid Access Error";
			break;
		case VALIDATION_ERR:
			error_message = "Validation Error";
			break;
		default:
			error_message = "Unhandled Error";
	}

	php_dom_throw_error_with_message(error_code, error_message, strict_error TSRMLS_CC);
}
