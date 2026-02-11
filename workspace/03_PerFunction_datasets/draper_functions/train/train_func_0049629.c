Draw(wxGrid &grid,
                        wxGridCellAttr &attr,
                        wxDC &dc,
                        const wxRect &rect,
                        int row,
                        int col,
                        bool isSelected)
{
   wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

   wxGridTableBase *table = grid.GetTable();
   TimeEditor *te = (TimeEditor *) grid.GetCellEditor(row, col);
   wxString tstr;

   if (te) {
      double value;

      table->GetValue(row, col).ToDouble(&value);

      TimeTextCtrl tt(&grid,
                      wxID_ANY,
                      wxT(""),
                      value,
                      te->GetRate(),
                      wxPoint(10000, 10000),
                      wxDefaultSize,
                      true);
      tt.SetFormatString(tt.GetBuiltinFormat(te->GetFormat()));
      tstr = tt.GetTimeString();

      te->DecRef();
   }

   dc.SetBackgroundMode(wxTRANSPARENT);

   if (grid.IsEnabled())
   {
      if (isSelected)
      {
         dc.SetTextBackground(grid.GetSelectionBackground());
         dc.SetTextForeground(grid.GetSelectionForeground());
      }
      else
      {
         dc.SetTextBackground(attr.GetBackgroundColour());
         dc.SetTextForeground(attr.GetTextColour());
      }
   }
   else
   {
      dc.SetTextBackground(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
      dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
   }

   dc.SetFont(attr.GetFont());

   int hAlign, vAlign;

   attr.GetAlignment(&hAlign, &vAlign);

   grid.DrawTextRectangle(dc, tstr, rect, hAlign, vAlign);
}
