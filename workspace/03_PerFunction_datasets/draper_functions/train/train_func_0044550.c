Merge(vtkUniformVariables *other)
{
  assert("pre: other_exists" && other!=0);
  assert("pre: not_self" && other!=this);

  other->Start();
  while(!other->IsAtEnd())
    {
    const char *name=other->GetCurrentName();
    UniformMapIt cur=other->Map->Map.find(name);

    vtkUniform *u1=(*cur).second;

    vtkUniform *u2=u1->Clone();
    vtksys_stl::pair<const char *, vtkUniform *> p;
    p.first=u2->GetName();
    p.second=u2;
    this->Map->Map.erase(p.first);
    this->Map->Map.insert(p);
    other->Next();
    }
  if(other->Map->Map.size()>0)
    {
    this->Modified();
    }
}
