InitPathTraversal()
{
  if ( this->Paths == NULL )
    {
    this->Paths = vtkAssemblyPaths::New();
    vtkAssemblyPath *path = vtkAssemblyPath::New();
    path->AddNode(this,NULL);
    this->BuildPaths(this->Paths,path);
    path->Delete();
    }
  this->Paths->InitTraversal();
}
