us_osc_msg_print( const us_osc_msg_t *self, us_print_t *printer )
{
    bool r = false;
    if ( self && printer )
    {
        us_osc_msg_element_t *cur = 0;
        r = true;
        r &= printer->printf( printer, "msg_t: address: '%s'\n", self->m_address );
        cur = self->m_first_element;
        while ( cur && r )
        {
            r &= cur->print( cur, printer );
            cur = cur->m_next;
        }
    }
    return r;
}
