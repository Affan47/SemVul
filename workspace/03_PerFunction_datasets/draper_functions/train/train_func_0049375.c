get_pix_aux (u_int16 x, u_int16 y, u_int32& col) const
{
    u_int8 * offset = ((Uint8 *) vis->pixels) + y * vis->pitch
        + x * vis->format->BytesPerPixel;

    switch (vis->format->BytesPerPixel)
    {
        case 1:
            col = *((Uint8 *)(offset));
            break;
        case 2:
            col = *((Uint16 *)(offset));
            break;
        case 3:
        {
            u_int8 r, g, b;
            col = 0;
            u_int32 t;

            r = *((offset) + (vis->format->Rshift >> 3));
            g = *((offset) + (vis->format->Gshift >> 3));
            b = *((offset) + (vis->format->Bshift >> 3));

            t = r << vis->format->Rshift;
            col |= t;
            t = g << vis->format->Gshift;
            col |= t;
            t = b << vis->format->Bshift;
            col |= t;

            break;
        }
        case 4:
            col = *((Uint32 *)(offset));
            break;
    }
}
