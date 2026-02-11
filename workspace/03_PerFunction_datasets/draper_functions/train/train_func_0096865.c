strip ( void )                             throw ( Exception )
{
    source = 0;

    if ( sinks ) {
        unsigned int    u;

        for ( u = 0; u < numSinks; ++u ) {
            sinks[u] = 0;
        }

        delete[] sinks;
    }
}
