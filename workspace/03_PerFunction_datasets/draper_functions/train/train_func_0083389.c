setField( const qint64 field )
{
    int index = m_fieldSelection->findData( field );
    m_fieldSelection->setCurrentIndex( index == -1 ? 0 : index );
}
