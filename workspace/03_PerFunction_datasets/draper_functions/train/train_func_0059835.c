codeAsString(int code)
{
    switch ( code ) {
    case INDEX_SIZE_ERR:
        return DOMString( "INDEX_SIZE_ERR" );
    case DOMSTRING_SIZE_ERR:
        return DOMString( "DOMSTRING_SIZE_ERR" );
    case HIERARCHY_REQUEST_ERR:
        return DOMString( "HIERARCHY_REQUEST_ERR" );
    case WRONG_DOCUMENT_ERR:
        return DOMString( "WRONG_DOCUMENT_ERR" );
    case INVALID_CHARACTER_ERR:
        return DOMString( "INVALID_CHARACTER_ERR" );
    case NO_DATA_ALLOWED_ERR:
        return DOMString( "NO_DATA_ALLOWED_ERR" );
    case NO_MODIFICATION_ALLOWED_ERR:
        return DOMString( "NO_MODIFICATION_ALLOWED_ERR" );
    case NOT_FOUND_ERR:
        return DOMString( "NOT_FOUND_ERR" );
    case NOT_SUPPORTED_ERR:
        return DOMString( "NOT_SUPPORTED_ERR" );
    case INUSE_ATTRIBUTE_ERR:
        return DOMString( "INUSE_ATTRIBUTE_ERR" );
    case INVALID_STATE_ERR:
        return DOMString( "INVALID_STATE_ERR" );
    case SYNTAX_ERR:
        return DOMString( "SYNTAX_ERR" );
    case INVALID_MODIFICATION_ERR:
        return DOMString( "INVALID_MODIFICATION_ERR" );
    case NAMESPACE_ERR:
        return DOMString( "NAMESPACE_ERR" );
    case INVALID_ACCESS_ERR:
        return DOMString( "INVALID_ACCESS_ERR" );
    case VALIDATION_ERR:
        return DOMString( "VALIDATION_ERR" );
    case TYPE_MISMATCH_ERR:
        return DOMString( "TYPE_MISMATCH_ERR" );
    case SECURITY_ERR:
        return DOMString( "SECURITY_ERR" );
    case NETWORK_ERR:
        return DOMString( "NETWORK_ERR" );
    case ABORT_ERR:
        return DOMString( "ABORT_ERR" );
    case URL_MISMATCH_ERR:
        return DOMString( "URL_MISMATCH_ERR" );
    case QUOTA_EXCEEDED_ERR:
        return DOMString( "QUOTA_EXCEEDED_ERR" );
    case TIMEOUT_ERR:
        return DOMString( "TIMEOUT_ERR" );
    case NOT_READABLE_ERR:
        return DOMString( "NOT_READABLE_ERR" );
    case DATA_CLONE_ERR:
        return DOMString( "DATA_CLONE_ERR" );
    case ENCODING_ERR:
        return DOMString( "ENCODING_ERR" );
    default:
        return DOMString( "(unknown exception code)" );
    }
}
