TableNameIsNew()
{
  if(this->Database == 0)
    {
    vtkErrorMacro(<<"TableNameIsNew() called with no open database!");
    return false;
    }

  if(this->TableName == "")
    {
    vtkErrorMacro(<<"TableNameIsNew() called but no table name specified.");
    return false;
    }

  vtkStringArray *tableNames = this->Database->GetTables();
  if(tableNames->LookupValue(this->TableName) == -1)
    {
    return true;
    }

  vtkErrorMacro(
    << "Table " << this->TableName << " already exists in the database.  "
    << "Please choose another name.");
  this->TableName = "";
  return false;
}
