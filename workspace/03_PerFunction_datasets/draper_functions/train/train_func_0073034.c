print_define( STD_NAMESPACE ostream& out,
                          const char* fname, const char* name )
{
    out << "#define DCMTK_";

    for( const char* pch = name; *pch; ++pch )
        out.put( *pch <= 'z' && *pch >= 'a' ? *pch - 'a' + 'A' : *pch == ' ' ? '_' : *pch );
    out << '_' << fname;
}
