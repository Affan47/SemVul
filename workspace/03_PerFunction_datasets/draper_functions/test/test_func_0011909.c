DeepCopy(vtkUniformVariables *other)
{
  assert("pre: other_exists" && other!=0);
  assert("pre: not_self" && other!=this);

  if(this->Map->Map.size()>0)
    {
    delete this->Map;
    this->Map=new vtkUniformVariablesMap;
    this->Modified();
    }
  this->Merge(other);
}
