setInvisible(ViewLayer::ViewLayerPlacement viewLayerPlacement) {
    if (viewLayerPlacement == ViewLayer::NewBottom) {
        m_pointRectBottom.svgVisible = false;
        m_pointRectBottom.processed = true;
        return;
    }

    m_pointRectTop.svgVisible = false;
    m_pointRectTop.processed = true;
}
