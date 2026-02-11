CanonicalViewRender(vtkRenderer *ren,
                                                    vtkVolume *vol )
{

  if ( this->ValidateRender(ren, vol ) )
    {

    this->GPURender( ren, vol);
    }
}
