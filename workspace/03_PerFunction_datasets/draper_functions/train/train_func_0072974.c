GetChild()

{


    if( poChild == NULL && nChildPos != 0 )
    {
        poChild = new HFAEntry( psHFA, nChildPos, this, NULL );
    }

    return( poChild );
}
