stack_global()
{
    static STACK result;
    if ( !stack )
    {
        int const size = 1 << 21;
        stack = BJAM_MALLOC( size );
        result.data = (char *)stack + size;
    }
    return &result;
}
