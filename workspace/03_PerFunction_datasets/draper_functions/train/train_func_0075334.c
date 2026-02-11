SetSelectionPainter(vtkPainter* p)
{
  if (this->SelectionPainter)
    {
    this->SelectionPainter->SetInformation(0);
    this->SelectionPainter->RemoveObservers(vtkCommand::ProgressEvent, this->Observer);
    }
  vtkSetObjectBodyMacro(SelectionPainter, vtkPainter, p);
   if (this->SelectionPainter)
    {
    this->SelectionPainter->AddObserver(vtkCommand::ProgressEvent, this->Observer);
    this->SelectionPainter->SetInformation(this->PainterInformation);
    }
}
