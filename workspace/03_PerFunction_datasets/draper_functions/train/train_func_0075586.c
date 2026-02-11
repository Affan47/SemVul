CloneOn( DDFModule *poTargetModule )

{


    int         i;

    for( i = 0; i < nFieldCount; i++ )
    {
        DDFFieldDefn    *poDefn = paoFields[i].GetFieldDefn();

        if( poTargetModule->FindFieldDefn( poDefn->GetName() ) == NULL )
            return NULL;
    }


    DDFRecord   *poClone;

    poClone = Clone();


    for( i = 0; i < nFieldCount; i++ )
    {
        DDFField        *poField = poClone->paoFields+i;
        DDFFieldDefn    *poDefn;

        poDefn = poTargetModule->FindFieldDefn(
            poField->GetFieldDefn()->GetName() );

        poField->Initialize( poDefn, poField->GetData(),
                             poField->GetDataSize() );
    }

    poModule->RemoveCloneRecord( poClone );
    poClone->poModule = poTargetModule;
    poTargetModule->AddCloneRecord( poClone );

    return poClone;
}
