IsDataAttributeCellBased( const char * attrName )
{
  int  cellBasd = -1;
  int  varIndex = -1;

  if ( attrName )
    {
    for ( unsigned int i = 0; i < this->Variables.size(); i ++ )
      {
      if (  strcmp( this->Variables[i].c_str(), attrName ) == 0  )
        {
        varIndex = i;
        break;
        }
      }

    cellBasd = ( varIndex == -1 ) ? -1: this->CellBased[ varIndex ];
    }

  return cellBasd;
}
