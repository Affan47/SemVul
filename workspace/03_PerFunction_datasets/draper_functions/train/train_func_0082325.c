xmlSchemaValidateLengthFacetInternal(xmlSchemaFacetPtr facet,
                                     xmlSchemaTypeType valType,
                                     const xmlChar *value,
                                     xmlSchemaValPtr val,
                                     unsigned long *length,
                                     xmlSchemaWhitespaceValueType ws)
{
    unsigned int len = 0;

    if ((length == NULL) || (facet == NULL))
        return (-1);
    *length = 0;
    if ((facet->type != XML_SCHEMA_FACET_LENGTH) &&
        (facet->type != XML_SCHEMA_FACET_MAXLENGTH) &&
        (facet->type != XML_SCHEMA_FACET_MINLENGTH))
        return (-1);


    if ((facet->val == NULL) ||
        ((facet->val->type != XML_SCHEMAS_DECIMAL) &&
         (facet->val->type != XML_SCHEMAS_NNINTEGER)) ||
        (facet->val->value.decimal.frac != 0)) {
        return(-1);
    }
    if ((val != NULL) && (val->type == XML_SCHEMAS_HEXBINARY))
        len = val->value.hex.total;
    else if ((val != NULL) && (val->type == XML_SCHEMAS_BASE64BINARY))
        len = val->value.base64.total;
    else {
        switch (valType) {
            case XML_SCHEMAS_STRING:
            case XML_SCHEMAS_NORMSTRING:
                if (ws == XML_SCHEMA_WHITESPACE_UNKNOWN) {


                    if (valType == XML_SCHEMAS_STRING)
                        len = xmlUTF8Strlen(value);
                    else
                        len = xmlSchemaNormLen(value);
                } else if (value != NULL) {
                    if (ws == XML_SCHEMA_WHITESPACE_COLLAPSE)
                        len = xmlSchemaNormLen(value);
                    else


                    len = xmlUTF8Strlen(value);
                }
                break;
            case XML_SCHEMAS_IDREF:
            case XML_SCHEMAS_TOKEN:
            case XML_SCHEMAS_LANGUAGE:
            case XML_SCHEMAS_NMTOKEN:
            case XML_SCHEMAS_NAME:
            case XML_SCHEMAS_NCNAME:
            case XML_SCHEMAS_ID:


            case XML_SCHEMAS_ANYURI:
                if (value != NULL)
                    len = xmlSchemaNormLen(value);
                break;
            case XML_SCHEMAS_QNAME:
            case XML_SCHEMAS_NOTATION:


                return (0);
            default:
                TODO
        }
    }
    *length = (unsigned long) len;


    if (facet->type == XML_SCHEMA_FACET_LENGTH) {
        if (len != facet->val->value.decimal.lo)
            return(XML_SCHEMAV_CVC_LENGTH_VALID);
    } else if (facet->type == XML_SCHEMA_FACET_MINLENGTH) {
        if (len < facet->val->value.decimal.lo)
            return(XML_SCHEMAV_CVC_MINLENGTH_VALID);
    } else {
        if (len > facet->val->value.decimal.lo)
            return(XML_SCHEMAV_CVC_MAXLENGTH_VALID);
    }

    return (0);
}
