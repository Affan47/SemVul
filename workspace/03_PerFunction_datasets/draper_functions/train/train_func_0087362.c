GetBounds()
{
  if ( ! this->GetExecutive()->GetInputData(0, 0) )
    {
    vtkMath::UninitializeBounds(this->Bounds);
    return this->Bounds;
    }
  else
    {
    this->Update();


    vtkCompositeDataPipeline * executive = vtkCompositeDataPipeline::SafeDownCast(this->GetExecutive());
    if( executive->GetPipelineMTime() > this->BoundsMTime.GetMTime() )
      {
      this->ComputeBounds();
      }

    return this->Bounds;
    }
}
