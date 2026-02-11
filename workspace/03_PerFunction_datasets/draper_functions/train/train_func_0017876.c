ComputeWorldPosition( vtkRenderer *ren,
                                                    double  displayPos[2],
                                                    double *refWorldPos,
                                                    double  worldPos[3],
                                                    double  worldOrient[9] )
{
  if ( !this->UpdateInternalState() )
    {
    return 0;
    }

  return this->Placer->ComputeWorldPosition( ren, displayPos,
                                             refWorldPos, worldPos,
                                             worldOrient );
}
