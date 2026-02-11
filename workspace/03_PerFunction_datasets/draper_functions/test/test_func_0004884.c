as_string( long n ) const
{
    NcValues* tmp = values();
    char* rval = tmp->as_string(n);
    delete tmp;
    return rval;
}
