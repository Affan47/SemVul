GetAttr( SDTSModId *poModId )

{
    SDTSAttrRecord *poAttrRecord;

    poAttrRecord = (SDTSAttrRecord *) GetIndexedFeatureRef( poModId );

    if( poAttrRecord == NULL )
        return NULL;

    return poAttrRecord->poATTR;
}
