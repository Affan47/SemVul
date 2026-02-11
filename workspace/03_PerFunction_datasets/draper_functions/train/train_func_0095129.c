httpRemoveOption(MprHash *options, cchar *field)
{
    if (options == 0) {
        mprAssert(options);
        return;
    }
    mprRemoveKey(options, field);
}
