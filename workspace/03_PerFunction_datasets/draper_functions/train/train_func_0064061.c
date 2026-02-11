createCollationElementIterator
                                           (const UnicodeString& source) const
{
    UErrorCode status = U_ZERO_ERROR;
    CollationElementIterator *result = new CollationElementIterator(source, this,
                                                                    status);
    if (U_FAILURE(status)) {
        delete result;
        return NULL;
    }

    return result;
}
