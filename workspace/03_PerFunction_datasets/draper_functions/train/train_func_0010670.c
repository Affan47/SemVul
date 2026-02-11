IsFieldIndexed( int nFieldId )

{
    if ( m_poDefn==NULL || m_pabFieldIndexed==NULL ||
         nFieldId < 0 || nFieldId >= m_poDefn->GetFieldCount())
        return FALSE;

    return m_pabFieldIndexed[nFieldId];
}
