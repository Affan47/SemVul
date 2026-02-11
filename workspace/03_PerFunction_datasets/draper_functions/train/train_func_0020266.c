Update()
{
  vtkPolyData *input = this->GetInput();


  if ( ! input )
    {
    vtkErrorMacro(<< "No input...can't execute!");
    return;
    }

  input->Update();

  if (input->GetMTime() > this->ExecuteTime ||
      this->GetMTime() > this->ExecuteTime )
    {
    if ( input->GetDataReleased() )
      {
      input->Update();
      }
    this->InvokeEvent(vtkCommand::StartEvent,NULL);


    this->AbortExecute = 0;
    this->Progress = 0.0;
    this->Execute();
    this->ExecuteTime.Modified();
    if ( !this->AbortExecute )
      {
      this->UpdateProgress(1.0);
      }

    this->InvokeEvent(vtkCommand::EndEvent,NULL);
    }
  if ( input->ShouldIReleaseData() )
    {
    input->ReleaseData();
    }

}
