exec_done( void )
{
    int i;
    for( i = 0; i < MAXJOBS; ++i )
    {
        if( ! cmdtab[i].action ) break;
        BJAM_FREE( cmdtab[i].action );
        BJAM_FREE( cmdtab[i].target );
    }
}
