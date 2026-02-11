SetValue(vtkIdType row, vtkIdType col, vtkVariant value)
{
  vtkAbstractArray* arr = this->GetColumn(col);
  if (!arr)
    {
    return;
    }
  int comps = arr->GetNumberOfComponents();
  if (vtkDataArray::SafeDownCast(arr))
    {
    vtkDataArray* data = vtkDataArray::SafeDownCast(arr);
    if (comps == 1)
      {
      data->SetVariantValue(row, value);
      }
    else
      {
      if (value.IsArray() && vtkDataArray::SafeDownCast(value.ToArray()) &&
          value.ToArray()->GetNumberOfComponents() == comps)
        {
        data->SetTuple(row, vtkDataArray::SafeDownCast(value.ToArray())->GetTuple(0));
        }
      else
        {
        vtkWarningMacro("Cannot assign this variant type to multi-component data array.");
        return;
        }
      }
    }
  else if (vtkStringArray::SafeDownCast(arr))
    {
    vtkStringArray* data = vtkStringArray::SafeDownCast(arr);
    if (comps == 1)
      {
      data->SetValue(row, value.ToString());
      }
    else
      {
      if (value.IsArray() && vtkStringArray::SafeDownCast(value.ToArray()) &&
          value.ToArray()->GetNumberOfComponents() == comps)
        {
        data->SetTuple(row, 0, vtkStringArray::SafeDownCast(value.ToArray()));
        }
      else
        {
        vtkWarningMacro("Cannot assign this variant type to multi-component string array.");
        return;
        }
      }
    }
  else if (vtkVariantArray::SafeDownCast(arr))
    {
    vtkVariantArray* data = vtkVariantArray::SafeDownCast(arr);
    if (comps == 1)
      {
      data->SetValue(row, value);
      }
    else
      {
      if (value.IsArray() && value.ToArray()->GetNumberOfComponents() == comps)
        {
        data->SetTuple(row, 0, value.ToArray());
        }
      else
        {
        vtkWarningMacro("Cannot assign this variant type to multi-component string array.");
        return;
        }
      }
    }
  else if(vtkUnicodeStringArray::SafeDownCast(arr))
    {
    vtkUnicodeStringArray* data = vtkUnicodeStringArray::SafeDownCast(arr);
    if(comps==1)
      {
      data->SetValue(row, value.ToUnicodeString());
      }
    else
      {
      if(value.IsArray() && vtkUnicodeStringArray::SafeDownCast(value.ToArray()) &&
         value.ToArray()->GetNumberOfComponents() == comps)
        {
        data->SetTuple(row, 0, vtkUnicodeStringArray::SafeDownCast(value.ToArray()));
        }
      else
        {
        vtkWarningMacro("Cannot assign this variant type to multi-component unicode string array.");
        return;
        }
      }
    }
  else
    {
    vtkWarningMacro("Unable to process array named " << col);
    }
}
