getShapeParams(int shapetype)
{
    if (shapetype < 0 || shapetype >= int(m_shapeTypes.size()) ||
        !m_shapeTypes[shapetype].isShape)
        return 0;
    return m_shapeTypes[shapetype].parameters;
}
