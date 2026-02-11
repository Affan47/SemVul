ajAcdGetTextall(const char *token)
{
    AjPTextall val = acdGetValueRef(token, "text");

    if(!val->Multi)
        ajWarn("ajAcdGetTextall request text input stream but maxreads is 1");

    return val;
}
