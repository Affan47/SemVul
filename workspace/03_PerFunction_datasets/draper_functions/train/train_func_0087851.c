activated()
{
    if ( weaver()->activeThreadCount() == 0 )
    {
        weaver()->setState( Suspended );
    }
}
