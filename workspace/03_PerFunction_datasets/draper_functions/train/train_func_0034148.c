GetFieldName(int column)
{
  if (! this->Active)
    {
    vtkErrorMacro(<<"GetFieldName(): Query is not active!");
    return NULL;
    }
  else if (column < 0 || column >= this->GetNumberOfFields())
    {
    vtkErrorMacro(<<"GetFieldName(): Illegal field index "
                  << column);
    return NULL;
    }
  else
    {
    return vtk_sqlite3_column_name(this->Statement, column);
    }
}
