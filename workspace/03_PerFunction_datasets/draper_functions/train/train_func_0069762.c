int104_add_uint (Int104  *x,
                 guint     y)
{
        gint    i;
        guint   temp, carry;

        carry = 0;
        for ( i = 12; i >= 0; i-- )
        {
                temp = x->byte[i] + (y & 0xFF) + carry;

                x->byte[i]  = temp & 0xFF;
                carry       = temp >> 8;
                y           = y >> 8;
        }
}
