setErrorCode(int errorCode)
{
    d->errorCode = errorCode;
    if (d->type != HelperError) {
        d->type = KAuthError;
    }
}
