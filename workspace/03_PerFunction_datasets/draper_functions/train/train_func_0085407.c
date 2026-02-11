us_mtc_extract_qf( us_mtc_t *self, int qf )
{
    int val;
    switch ( qf )
    {
    case 0:
        val = self->m_frame & 0xf;
        break;
    case 1:
        val = ( self->m_frame >> 4 ) & 0xf;
        break;
    case 2:
        val = self->m_second & 0xf;
        break;
    case 3:
        val = ( self->m_second >> 4 ) & 0xf;
        break;
    case 4:
        val = self->m_minute & 0xf;
        break;
    case 5:
        val = ( self->m_minute >> 4 ) & 0xf;
        break;
    case 6:
        val = self->m_hour & 0xf;
        break;
    case 7:
        val = ( ( self->m_hour >> 4 ) & 0x1 ) + ( us_mtc_typecode[self->m_fmt] << 1 );
        break;
    default:
        val = 0;
        break;
    }
    return val;
}
