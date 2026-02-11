ClearSR(HFAHandle hHFA)
{
    for( int iBand = 0; iBand < hHFA->nBands; iBand++ )
    {
        HFAEntry	*poMIEntry;
        if( hHFA->papoBand[iBand]->poNode && (poMIEntry = hHFA->papoBand[iBand]->poNode->GetNamedChild("Projection")) != NULL )
        {
            poMIEntry->MarkDirty();
            poMIEntry->SetIntField( "proType", 0 );
            poMIEntry->SetIntField( "proNumber", 0 );
            poMIEntry->SetStringField( "proExeName", "");
            poMIEntry->SetStringField( "proName", "");
            poMIEntry->SetIntField( "proZone", 0 );
            poMIEntry->SetDoubleField( "proParams[0]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[1]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[2]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[3]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[4]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[5]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[6]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[7]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[8]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[9]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[10]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[11]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[12]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[13]", 0.0 );
            poMIEntry->SetDoubleField( "proParams[14]", 0.0 );
            poMIEntry->SetStringField( "proSpheroid.sphereName", "" );
            poMIEntry->SetDoubleField( "proSpheroid.a", 0.0 );
            poMIEntry->SetDoubleField( "proSpheroid.b", 0.0 );
            poMIEntry->SetDoubleField( "proSpheroid.eSquared", 0.0 );
            poMIEntry->SetDoubleField( "proSpheroid.radius", 0.0 );
            HFAEntry* poDatumEntry = poMIEntry->GetNamedChild("Datum");
            if( poDatumEntry != NULL )
            {
                poDatumEntry->MarkDirty();
                poDatumEntry->SetStringField( "datumname", "" );
                poDatumEntry->SetIntField( "type", 0 );
                poDatumEntry->SetDoubleField( "params[0]", 0.0 );
                poDatumEntry->SetDoubleField( "params[1]", 0.0 );
                poDatumEntry->SetDoubleField( "params[2]", 0.0 );
                poDatumEntry->SetDoubleField( "params[3]", 0.0 );
                poDatumEntry->SetDoubleField( "params[4]", 0.0 );
                poDatumEntry->SetDoubleField( "params[5]", 0.0 );
                poDatumEntry->SetDoubleField( "params[6]", 0.0 );
                poDatumEntry->SetStringField( "gridname", "" );
            }
            poMIEntry->FlushToDisk();
            char* peStr = HFAGetPEString( hHFA );
            if( peStr != NULL && strlen(peStr) > 0 )
                HFASetPEString( hHFA, "" );
        }
    }
    return;
}
