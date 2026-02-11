transform( float *p )
{
    if( m_num == 8 )
        transform8( p );
    else
        _transform( p, m_num, 0 );
}
