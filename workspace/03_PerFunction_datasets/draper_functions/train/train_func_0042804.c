RedrawDataCurve(int index, int min_index, int max_index)
{
    if (m_batch_count) return;

    wxCHECK_RET((index>=0)&&(index<(int)m_curves.GetCount()), wxT("invalid curve index"));

    wxPlotData *plotData = GetDataCurve(index);
    wxCHECK_RET(plotData, wxT("not a data curve"));

    int count = plotData->GetCount();
    wxCHECK_RET((min_index<=max_index)&&(min_index>=0)&&(max_index>=0)&&(min_index<count)&&(max_index<count), wxT("invalid data index"));

    wxRect rect(m_areaClientRect);
    int cursor_size = GetCursorSize();

    if (plotData->GetIsXOrdered())
    {
        double x = plotData->GetXValue(wxMax(min_index-1, 0));

        if (x > m_viewRect.GetRight())
            return;
        else if (x < m_viewRect.m_x)
            rect.x = 0;
        else
            rect.x = GetClientCoordFromPlotX(x) - cursor_size/2 - 1;

        x = plotData->GetXValue(wxMin(max_index+1, (int)plotData->GetCount()-1));

        if (x < m_viewRect.m_x)
            return;
        else if (x > m_viewRect.GetRight())
            rect.SetRight(m_areaClientRect.width);
        else
            rect.SetRight(GetClientCoordFromPlotX(x) + cursor_size/2 + 1);

        rect.Intersect(m_areaClientRect);
    }

    wxMemoryDC mdc;
    mdc.SelectObject( m_area->m_bitmap );
    DrawDataCurve( &mdc, plotData, index, rect );
    DrawCurveCursor(&mdc);
    wxClientDC dc(m_area);
    dc.Blit(rect.x, rect.y, rect.width, rect.height, &mdc, rect.x, rect.y);
    mdc.SelectObject( wxNullBitmap );
}
