SetResliceImageViewer( vtkResliceImageViewer *i )
{

  this->ResliceImageViewer = i;

  if(i)
    {

    i->GetResliceCursor()
      ->AddObserver( vtkResliceCursorWidget::ResliceAxesChangedEvent,
        this->EventCallbackCommand );
    i->GetResliceCursor()
      ->AddObserver( vtkResliceCursorWidget::ResliceAxesChangedEvent,
        this->EventCallbackCommand );
    }
}
