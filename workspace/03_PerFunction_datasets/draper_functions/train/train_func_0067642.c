xsltFunctionLocalTime(xmlXPathParserContextPtr ctxt, int nargs) {
    xmlXPathObjectPtr obj;
    char *str;
    char digits[5];
    char result[29];
    long int field;
    time_t gmt, lmt;
    struct tm gmt_tm;
    struct tm *local_tm;

    if (nargs != 1) {
       xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
                      "localTime() : invalid number of args %d\n", nargs);
       ctxt->error = XPATH_INVALID_ARITY;
       return;
    }

    obj = valuePop(ctxt);

    if (obj->type != XPATH_STRING) {
	obj = xmlXPathConvertString(obj);
    }
    if (obj == NULL) {
	valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
	return;
    }

    str = (char *) obj->stringval;


    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+7, 4);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_year = field - 1900;

    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+12, 2);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_mon = field - 1;

    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+15, 2);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_mday = field;

    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+18, 2);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_hour = field;

    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+21, 2);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_min = field;

    memset(digits, 0, sizeof(digits));
    strncpy(digits, str+24, 2);
    field = strtol(digits, NULL, 10);
    gmt_tm.tm_sec = field;


    gmt = mktime(&gmt_tm);


    local_tm = localtime(&gmt);


    lmt = gmt - timezone;


    local_tm = localtime(&lmt);


    str = asctime(local_tm);


    memset(result, 0, sizeof(result));


    strncpy(result, str, 20);
    strcpy(result+20, "???");
    strncpy(result+23, str+19, 5);


    valuePush(ctxt, xmlXPathNewString((xmlChar *)result));
}
