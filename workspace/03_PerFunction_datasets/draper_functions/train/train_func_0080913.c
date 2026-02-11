setHighlightData(short z, short y, short x, UCHAR value)
{
    if ((y < 0) || (x < 0) || (z < 0) || (y > m_height - 1) || (x > m_width - 1)
        || (z > m_depth - 1)) {
        return;
    }

    Highlight[(z * m_width * m_height) + (y * m_width) + x] = value;
}
