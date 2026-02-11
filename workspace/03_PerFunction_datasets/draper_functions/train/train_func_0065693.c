RemoveMarker(int marker)
{
    wxCHECK_RET((marker >= 0) && (marker < (int)m_plotMarkers.GetCount()), wxT("Invalid marker number"));
    m_plotMarkers.RemoveAt(marker);
}
