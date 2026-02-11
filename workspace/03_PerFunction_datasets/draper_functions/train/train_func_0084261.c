getWantedSize() const
{
    switch ( m_unit ) {
        case 0:
            return static_cast<quint64>( m_size ) * Q_INT64_C( 1000 );
        case 1:
            return static_cast<quint64>( m_size ) * Q_INT64_C( 1000000 );
        case 2:
            return static_cast<quint64>( m_size ) * Q_INT64_C( 1000000000 );
        case 3:
            return static_cast<quint64>( m_size ) * Q_INT64_C( 1000000000000 );
        default:
            return static_cast<quint64>( m_size ) * Q_INT64_C( 1 );
    }
}
