RemapPNamesBasedOnProjCSAndPName( OGRSpatialReference* pOgr, const char* pszProgCSName,
                                                                     char **mappingTable )
{
  long ret = 0;
  OGR_SRSNode *poPROJCS = pOgr->GetAttrNode( "PROJCS" );
  for( int i = 0; mappingTable[i] != NULL; i += 3 )
  {
    while( mappingTable[i] != NULL && EQUALN(pszProgCSName, mappingTable[i], strlen(mappingTable[i])) )
    {
      OGR_SRSNode *poParm;
      const char* pszParamName = mappingTable[i+1];
      for( int iChild = 0; iChild < poPROJCS->GetChildCount(); iChild++ )
      {
          poParm = poPROJCS->GetChild( iChild );

          if( EQUAL(poParm->GetValue(),"PARAMETER")
              && poParm->GetChildCount() == 2
              && EQUAL(poParm->GetChild(0)->GetValue(),pszParamName) )
          {
              poParm->GetChild(0)->SetValue( mappingTable[i+2] );
              break;
          }
      }
      ret ++;
      i += 3;
    }
    if (ret > 0)
      break;
  }
  return ret;
}
