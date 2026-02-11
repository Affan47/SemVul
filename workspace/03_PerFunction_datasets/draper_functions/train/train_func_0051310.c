adjustFloatingBlock(const MarginInfo& marginInfo)
{


    int marginOffset = marginInfo.canCollapseWithTop() ? 0 : marginInfo.margin();
    m_height += marginOffset;
    positionNewFloats();
    m_height -= marginOffset;
}
