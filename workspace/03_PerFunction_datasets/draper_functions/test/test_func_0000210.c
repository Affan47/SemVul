flimage_set_fits_bits( int bits )
{
    int old = fits_bit;

    if ( bits > 0 && bits < 16 )
    {
        fits_bit = bits;
        return old;
    }

	return - old;
}
