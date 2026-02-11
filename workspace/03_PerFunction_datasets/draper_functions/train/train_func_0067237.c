CopyParameters
  ( vtkAbstractInterpolatedVelocityField * from )
{
  this->Superclass::CopyParameters( from );

  if (  from->IsA( "vtkCellLocatorInterpolatedVelocityField" )  )
    {
    this->SetCellLocatorPrototype
          (  vtkCellLocatorInterpolatedVelocityField::SafeDownCast( from )
             ->GetCellLocatorPrototype()
          );
    }
}
