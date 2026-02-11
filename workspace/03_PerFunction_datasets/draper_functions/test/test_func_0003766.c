getShapeHasNoParams(int shapetype)
{
    if (shapetype < int(m_shapeTypes.size()))
        return m_shapeTypes[shapetype].shouldHaveNoParams;
    return false;
}
