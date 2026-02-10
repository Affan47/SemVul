BuildRepresentation()
{

  if ( this->GetMTime() > this->BuildTime ||
       (this->Renderer && this->Renderer->GetVTKWindow() &&
        this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime) )
    {
    if ( ! this->Placed )
      {
      this->ValidPick = 1;
      this->Placed = 1;
      }

    this->SizeBounds();
    this->Sphere->Update();
    this->BuildTime.Modified();
    }
}
