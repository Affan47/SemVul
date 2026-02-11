SetColorWindow( double w )
{
  double rmin = this->GetColorLevel() - 0.5*fabs( w );
  double rmax = rmin + fabs( w );
  this->GetLookupTable()->SetRange( rmin, rmax );

  this->WindowLevel->SetWindow(w);
  if (vtkResliceCursorRepresentation *rep =
        vtkResliceCursorRepresentation::SafeDownCast(
          this->ResliceCursorWidget->GetRepresentation()))
    {
    rep->SetWindowLevel(w, rep->GetLevel(), 1);
    }
}
