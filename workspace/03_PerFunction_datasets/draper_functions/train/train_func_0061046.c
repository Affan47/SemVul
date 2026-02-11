slotDatabaseWritten( bool success )
{
    DEBUG_BLOCK
    Q_UNUSED( success )

    emit endProgressOperation( this );

    m_memColl->collectionUpdated();
}
