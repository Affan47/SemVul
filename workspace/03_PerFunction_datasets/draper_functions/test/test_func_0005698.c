BuildRepresentation()
{

  if ( this->GetMTime() > this->BuildTime ||
       (this->Renderer && this->Renderer->GetVTKWindow() &&
        this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime) )
    {


    this->UpdateHandle();


    this->UpdateLabel();

    this->BuildTime.Modified();
    }
}
