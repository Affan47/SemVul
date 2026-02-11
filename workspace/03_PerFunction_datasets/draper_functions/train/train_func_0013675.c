SetUniformfv(const char *name,
                                       int numberOfComponents,
                                       int numberOfElements,
                                       float *value)
{
  assert("pre: name_exists" && name!=0);
  assert("pre: value_exists" && value!=0);
  assert("pre: valid_numberOfComponents" && numberOfComponents>=1 && numberOfComponents<=4);
  assert("pre: valid_numberOfElements" && numberOfElements>=1);

  UniformMapIt cur=this->Map->Map.find(name);

  if(cur!=this->Map->Map.end())
    {
    vtkUniform *u=(*cur).second;
    vtkUniformArrayFloat *uf=0;
    if(u->GetClassType()==vtkUniform::ClassTypeArrayFloat)
      {
      uf=static_cast<vtkUniformArrayFloat *>(u);
      }
    if(uf==0)
      {
      vtkErrorMacro(<<"try to overwrite a value with different type.");
      }
    else
      {
      if(uf->GetSize()!=numberOfComponents)
        {
        vtkErrorMacro(<<"try to overwrite a value of same type but different number of components.");
        }
      if(uf->GetArraySize()!=numberOfElements)
        {
        vtkErrorMacro(<<"try to overwrite a value of same type but different number of elements.");
        }
      else
        {
        bool changed=false;
        int i=0;
        while(!changed && i<numberOfComponents*numberOfElements)
          {
          changed=value[i]!=uf->GetValues()[i];
          ++i;
          }
        if(changed)
          {
          uf->SetValues(value);
          this->Modified();
          }
        }
      }
    }
  else
    {
    vtkUniform *u=0;
    u=new vtkUniformArrayFloat(numberOfComponents,numberOfElements,value);
    u->SetName(name);

    vtksys_stl::pair<const char *, vtkUniform *> p;
    p.first=u->GetName();

    p.second=u;

    this->Map->Map.insert(p);
    this->Modified();
    }
}
