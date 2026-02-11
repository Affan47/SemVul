menuBar()
{
    KMenuBar * mb = internalMenuBar(this);
    if ( !mb ) {
        mb = new KMenuBar( this );


        setMenuBar(mb);
    }
    return mb;
}
