GetArrayName ( vtkExodusReader::ArrayType type,
    int id )
{
  switch (type)
    {
    case vtkExodusReader::CELL:
      return this->GetCellArrayName( id );
      break;
    case vtkExodusReader::POINT:
      return this->GetPointArrayName( id );
      break;
    case vtkExodusReader::BLOCK:
      return this->GetBlockArrayName( id );
      break;
    case vtkExodusReader::PART:
      return this->GetPartArrayName( id );
      break;
    case vtkExodusReader::MATERIAL:
      return this->GetMaterialArrayName( id );
      break;
    case vtkExodusReader::ASSEMBLY:
      return this->GetAssemblyArrayName( id );
      break;
    case vtkExodusReader::HIERARCHY:
      return this->GetHierarchyArrayName( id );
      break;
    case vtkExodusReader::NUM_ARRAY_TYPES:
    case vtkExodusReader::UNKNOWN_TYPE:
    default:
      break;
    }

  return NULL;
}
