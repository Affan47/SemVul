SetInteractor(vtkRenderWindowInteractor *rwi)
{
  if (this->Interactor != rwi)
    {

    vtkRenderWindowInteractor *temp = this->Interactor;
    this->Interactor = rwi;
    if (temp != NULL) {temp->UnRegister(this);}
    if (this->Interactor != NULL)
      {
      this->Interactor->Register(this);

      int isize[2];
      this->Interactor->GetSize(isize);
      if (0 == isize[0] && 0 == isize[1])
        {
        this->Interactor->SetSize(this->GetSize());
        }

      if (this->Interactor->GetRenderWindow() != this)
        {
        this->Interactor->SetRenderWindow(this);
        }
      }
    }
}
