DrawWholePlot( wxDC *dc, const wxRect &boundingRect, int dpi )
{
    wxCHECK_RET(dc, wxT("invalid dc"));
    wxCHECK_RET(dpi > 0, wxT("Invalid dpi for plot drawing"));

    wxSize clientSize = GetClientSize();
    int sb_width = m_yAxisScrollbar->GetSize().GetWidth();
    clientSize.x -= sb_width;
    clientSize.y -= sb_width;


    double fontScale = (double)dpi / 72.0;

    double penScale = (m_pen_print_width / 25.4) * dpi;


    wxFont oldAxisLabelFont = GetAxisLabelFont();
    wxFont oldPlotTitleFont = GetPlotTitleFont();
    int old_area_border_width = m_area_border_width;
    int old_border = m_border;
    int old_cursor_size = m_cursorMarker.GetSize().x;
    wxPoint2DDouble old_zoom = m_zoom;
    wxRect2DDouble  old_view = m_viewRect;


    m_area_border_width = RINT(m_area_border_width * penScale);
    m_border = RINT(m_border * penScale);


    m_cursorMarker.SetSize(wxSize(int(old_cursor_size * penScale), int(old_cursor_size * penScale)));


    wxFont axisLabelFont = GetAxisLabelFont();
    axisLabelFont.SetPointSize( wxMax(2, RINT(axisLabelFont.GetPointSize() * fontScale)) );
    SetAxisLabelFont( axisLabelFont );

    wxFont plotTitleFont = GetPlotTitleFont();
    plotTitleFont.SetPointSize( wxMax(2, RINT(plotTitleFont.GetPointSize() * fontScale)) );
    SetPlotTitleFont( plotTitleFont );


    m_zoom = old_zoom;
    m_viewRect = old_view;


    DoSize( boundingRect );


    dc->SetDeviceOrigin(long(boundingRect.x+m_xAxisRect.GetLeft()),
                        long(boundingRect.y+m_xAxisRect.GetTop()));
    CalcXAxisTickPositions();
    DrawXAxis(dc, false);

    dc->SetDeviceOrigin(long(boundingRect.x+m_yAxisRect.GetLeft()),
                        long(boundingRect.y+m_yAxisRect.GetTop()));
    CalcYAxisTickPositions();
    DrawYAxis(dc, false);

    dc->SetDeviceOrigin(long(boundingRect.x+m_areaRect.GetLeft()),
                        long(boundingRect.y+m_areaRect.GetTop()));
    DrawAreaWindow(dc, m_areaClientRect);

    dc->SetDeviceOrigin(boundingRect.x, boundingRect.y);
    DrawPlotCtrl(dc);


    m_area_border_width = old_area_border_width;
    m_border = old_border;
    m_cursorMarker.SetSize(wxSize(old_cursor_size, old_cursor_size));

    SetAxisLabelFont( oldAxisLabelFont );
    SetPlotTitleFont( oldPlotTitleFont );
    m_zoom     = old_zoom;
    m_viewRect = old_view;


    UpdateWindowSize();
    Redraw(wxPLOT_REDRAW_WHOLEPLOT);
}
