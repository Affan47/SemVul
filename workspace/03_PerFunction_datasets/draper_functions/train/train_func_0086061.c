ocurisetparams(OCURI* uri, const char* newparams)
{
    if(uri == NULL) return 0;
    if(uri->paramlist != NULL) ocparamfree(uri->paramlist);
    uri->paramlist = NULL;
    if(uri->params != NULL) free(uri->params);
    uri->params = nulldup(newparams);
    return 1;
}
