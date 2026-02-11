BuildURL(CPLString *url, const GDALWMSImageRequestInfo &iri, const char* pszRequest) {

    CPLLocaleC oLocaleEnforcer;
    *url = m_base_url;
    if (m_base_url.ifind( "service=") == std::string::npos)
        URLAppend(url, "&service=WMS");
    URLAppendF(url, "&request=%s", pszRequest);
    URLAppendF(url, "&version=%s", m_version.c_str());
    URLAppendF(url, "&layers=%s", m_layers.c_str());
    URLAppendF(url, "&styles=%s", m_styles.c_str());
    if (m_srs.size()) URLAppendF(url, "&srs=%s", m_srs.c_str());
    if (m_crs.size()) URLAppendF(url, "&crs=%s", m_crs.c_str());
    if (m_transparent.size()) URLAppendF(url, "&transparent=%s", m_transparent.c_str());
    URLAppendF(url, "&format=%s", m_image_format.c_str());
    URLAppendF(url, "&width=%d", iri.m_sx);
    URLAppendF(url, "&height=%d", iri.m_sy);
    URLAppendF(url, "&bbox=%.8f,%.8f,%.8f,%.8f",
        GetBBoxCoord(iri, m_bbox_order[0]), GetBBoxCoord(iri, m_bbox_order[1]),
        GetBBoxCoord(iri, m_bbox_order[2]), GetBBoxCoord(iri, m_bbox_order[3]));
}
