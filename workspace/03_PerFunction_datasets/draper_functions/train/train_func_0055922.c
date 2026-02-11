Ns_GetCharsetEncodingEx(char *charset, int len)
{
    Tcl_HashEntry *hPtr;
    Tcl_Encoding encoding;
    Ns_DString ds;


    Ns_DStringInit(&ds);
    Ns_DStringNAppend(&ds, charset, len);
    charset = Ns_StrTrim(Ns_StrToLower(ds.string));
    hPtr = Tcl_FindHashEntry(&charsets, charset);
    if (hPtr != NULL) {
	charset = Tcl_GetHashValue(hPtr);
    }
    encoding = Ns_GetEncoding(charset);
    Ns_DStringFree(&ds);
    return encoding;
}
