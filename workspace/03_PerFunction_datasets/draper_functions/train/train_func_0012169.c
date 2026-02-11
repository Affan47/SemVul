setAmoebaAt (int16_t x, int16_t y, Amoeba *amoeba)
{
    if ( 0 <= x && x < k_GridWidth &&
         0 <= y && y < k_GridHeight )
    {
        m_Grid[y * k_GridWidth + x] = amoeba;
    }
}
