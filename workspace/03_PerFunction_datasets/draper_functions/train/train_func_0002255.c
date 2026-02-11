GetArrayTypeID( const char *type )
{
  if ( strcmp( type, "CELL" ) == 0 )
    {
    return vtkExodusReader::CELL;
    }
  else if ( strcmp( type, "POINT" ) == 0 )
    {
    return vtkExodusReader::POINT;
    }
  else if ( strcmp( type, "BLOCK" ) == 0 )
    {
    return vtkExodusReader::BLOCK;
    }
  else if ( strcmp( type, "PART" ) == 0 )
    {
    return vtkExodusReader::PART;
    }
  else if ( strcmp( type, "MATERIAL" ) == 0 )
    {
    return vtkExodusReader::MATERIAL;
    }
  else if ( strcmp( type, "ASSEMBLY" ) == 0 )
    {
    return vtkExodusReader::ASSEMBLY;
    }
  else if ( strcmp( type, "HIERARCHY" ) == 0 )
    {
    return vtkExodusReader::HIERARCHY;
    }
  else
    {
    return vtkExodusReader::UNKNOWN_TYPE;
    }
}
