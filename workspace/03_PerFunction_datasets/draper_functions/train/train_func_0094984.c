Get_haccessDocumentRoot( string& shaccessDocumentRoot ) const
{
  ASSERT_VALID_CONFIG;
  m_pConfig->GetVariableValue( CFG_STR_HACCESSDOCUMENTROOT, shaccessDocumentRoot );


  if( shaccessDocumentRoot.size() == 0 )
    shaccessDocumentRoot = CFG_DFLT_HACCESSDOCUMENTROOT;

  replace( shaccessDocumentRoot, "\\", "/" );
}
