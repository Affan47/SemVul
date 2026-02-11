Probe()
{
  if(!this->Probed)
    {
    this->Probed=true;
    this->Array=new vtkGPUInfoListArray;
    this->Array->v.resize(0);
    }
  assert("post: probed" && this->IsProbed());
}
