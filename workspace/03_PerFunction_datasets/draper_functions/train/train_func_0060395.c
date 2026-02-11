double_size(const surface & src)
{
    u_int32 col;

    lock ();
    src.lock ();

    dbl_mode = src.is_dbl_mode ();
    resize(src.length(), src.height());
    for (u_int16 j = 0; j < height(); j++)
        for (u_int16 i = 0; i < length(); i++)
        {
            src.get_pix_aux(i, j, col);
            put_pix(i, j, col);
        }

    src.unlock ();
    unlock ();
}
