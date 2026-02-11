AddFeature( OGRGeometry* poGeometry )
{
    bool bAdded = false;


    if( NULL != poGeometry )
    {
        OGRFeature* poFeature = NULL;
        poFeature = new OGRFeature( poLayer_->GetLayerDefn() );
        poFeature->SetGeometryDirectly( poGeometry );

        bAdded = AddFeature( poFeature );
    }

    return bAdded;
}
