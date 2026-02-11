xmlTextReaderValidityWarningRelay(void *ctx, const char *msg, ...)
{
        xmlTextReaderPtr reader = (xmlTextReaderPtr) ctx;
        char * str;
        va_list ap;

        va_start(ap,msg);
        str = xmlTextReaderBuildMessage(msg,ap);
        if (!reader->errorFunc) {
                xmlTextReaderValidityWarning(ctx, "%s", str);
        } else {
                reader->errorFunc(reader->errorFuncArg, str, XML_PARSER_SEVERITY_VALIDITY_WARNING, NULL );
        }
        if (str != NULL)
                xmlFree(str);
        va_end(ap);
}
