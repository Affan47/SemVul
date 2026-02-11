lookup_func( const string & name, t_CKINT climb )
{
    Chuck_Func * f = func.lookup( name, climb );
    if( climb > 0 && !f && parent )
        return parent->lookup_func( name, climb );
    return f;
}
