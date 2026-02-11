se_LinkFaces( tControlledPTR< eFace >& old, eFace* replacement )
{
    tASSERT( old != replacement );


    if ( old->GetRefcount() > 1 )
    {
        eReplacementStorage& storage = old->GetReplacementStorage();
        storage.push_back( replacement );
    }
}
