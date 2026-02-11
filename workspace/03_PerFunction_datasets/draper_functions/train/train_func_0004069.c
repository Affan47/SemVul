AddProperty( GMLPropertyDefn *poDefn )

{
    if( GetProperty(poDefn->GetName()) != NULL )
    {
        CPLError(CE_Warning, CPLE_AppDefined,
                 "Field with same name (%s) already exists. Skipping newer ones",
                 poDefn->GetName());
        return -1;
    }

    m_nPropertyCount++;
    m_papoProperty = (GMLPropertyDefn **)
        CPLRealloc( m_papoProperty, sizeof(void*) * m_nPropertyCount );

    m_papoProperty[m_nPropertyCount-1] = poDefn;

    return m_nPropertyCount-1;
}
