getLiquidLevel(float x, float y)
{
    if (!m_liquid_map)
        return m_liquidLevel;

    x = MAP_RESOLUTION * (32 - x / SIZE_OF_GRIDS);
    y = MAP_RESOLUTION * (32 - y / SIZE_OF_GRIDS);

    int cx_int = ((int)x & (MAP_RESOLUTION - 1)) - m_liquid_offY;
    int cy_int = ((int)y & (MAP_RESOLUTION - 1)) - m_liquid_offX;

    if (cx_int < 0 || cx_int >= m_liquid_height)
        return INVALID_HEIGHT_VALUE;

    if (cy_int < 0 || cy_int >= m_liquid_width)
        return INVALID_HEIGHT_VALUE;

    return m_liquid_map[cx_int * m_liquid_width + cy_int];
}
