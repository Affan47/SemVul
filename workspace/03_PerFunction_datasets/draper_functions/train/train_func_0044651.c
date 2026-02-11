CalculateOffsets(float &sectorSize, float &woffset, float &hoffset)
{
    sectorSize = ((float)width())/m_map->columns();
    if (height()/m_map->rows() < sectorSize)
        sectorSize = ((float)height())/m_map->rows();

    woffset = ((float)width() - m_map->columns()*sectorSize)/2;
    hoffset = ((float)height() - m_map->rows()*sectorSize)/2;
}
