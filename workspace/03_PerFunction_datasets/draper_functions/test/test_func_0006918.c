Open    ( std::ifstream& f,
                      const char* filename   ) const
{
    if ( !tPath::IsValidPath( filename ) )
        return false;

    tArray< tString > paths;
    Paths( paths );

    for ( int prio = paths.Len() - 1; prio>=0; --prio )
    {


        tString fullname;
        fullname << paths( prio ) << "/" << filename;

#ifdef PRINTSEARCH
#endif


        f.clear();
        f.open( fullname );


        if ( f && f.good() )
        {
#ifdef PRINTSEARCH
            std::cout << "Trying to open " << fullname << " succeeded.";
#endif


            return true;
        }

#ifdef PRINTSEARCH
        std::cout << "Trying to open " << fullname << " succeeded.";
#endif
    }

    return false;
}
