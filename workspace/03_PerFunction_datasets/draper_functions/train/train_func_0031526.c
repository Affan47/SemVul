Scale(double eventPos[2])
{

  double sf = this->Glypher->GetScaleFactor();


  int *size = this->Renderer->GetSize();
  double dPos = static_cast<double>(eventPos[1]-this->LastEventPosition[1]);
  sf *= (1.0 + 2.0*(dPos / size[1]));


  this->Glypher->SetScaleFactor(sf);
  if(this->ShowSelectedNodes && this->SelectedNodesGlypher)
    {
    this->SelectedNodesGlypher->SetScaleFactor(sf);
    }
}
