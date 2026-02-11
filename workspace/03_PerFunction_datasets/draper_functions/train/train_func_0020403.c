Refresh(bool eraseb, const wxRect* rect_)
{


    if (GetBatchCount())
        return;

    if (rect_)
    {
        const wxRect rect(*rect_);
        const int rowLabelWidth  = GetRowLabelWidth();
        const int colLabelHeight = GetColLabelHeight();
        const wxSize extentSize(GetGridExtent());

        wxRect cornerRect(0, 0, rowLabelWidth, colLabelHeight);
        cornerRect.Intersect(rect);

        wxRect rowLabelRect(0, colLabelHeight, rowLabelWidth, extentSize.y);
        rowLabelRect.Intersect(rect);
        rowLabelRect.y -= colLabelHeight;

        wxRect colLabelRect(rowLabelWidth, 0, extentSize.x, colLabelHeight);
        colLabelRect.Intersect(rect);
        colLabelRect.x -= rowLabelWidth;

        wxRect gridRect(rowLabelWidth, colLabelHeight, extentSize.x, extentSize.y);
        gridRect.Intersect(rect);
        gridRect.x -= rowLabelWidth;
        gridRect.y -= colLabelHeight;

        if ( !wxRectIsEmpty(cornerRect) )
            RefreshCornerLabelWindow(eraseb, &cornerRect);
        if ( !wxRectIsEmpty(rowLabelRect) )
            RefreshRowLabelWindow(eraseb, &rowLabelRect);
        if ( !wxRectIsEmpty(colLabelRect) )
            RefreshColLabelWindow(eraseb, &colLabelRect);
        if ( !wxRectIsEmpty(gridRect) )
            RefreshGridWindow(eraseb, &gridRect);
    }
    else
    {
        RefreshCornerLabelWindow(eraseb, NULL);
        RefreshRowLabelWindow(eraseb, NULL);
        RefreshColLabelWindow(eraseb, NULL);
        RefreshGridWindow(eraseb, NULL);
    }
}
