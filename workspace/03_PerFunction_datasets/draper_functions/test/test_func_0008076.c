UpdatePaths()
{
  if (this->GetMTime() > this->PathTime ||
      (this->Paths && this->Paths->GetMTime() > this->PathTime))
    {
    if (this->Paths)
      {
      this->Paths->Delete();
      }


    this->Paths = vtkAssemblyPaths::New();
    vtkAssemblyPath *path = vtkAssemblyPath::New();


    path->AddNode(this, this->GetMatrix());


    vtkImageSlice *image = this->GetActiveImage();

    if (image)
      {
      path->AddNode(image, image->GetMatrix());
      image->BuildPaths(this->Paths, path);
      path->DeleteLastNode();
      }

    path->Delete();
    this->PathTime.Modified();
    }
}
