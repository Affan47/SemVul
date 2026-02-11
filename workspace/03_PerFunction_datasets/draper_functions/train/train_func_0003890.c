indent(int l)
{
    ostringstream s;
    for( int i=0; i<l; ++i )
        s.put(' ');
    return s.str();
}
