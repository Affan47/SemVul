IsInsideString(wxString& Line)
{
  int EndStringPos = Line.Find(_T('\"'));
  bool OutsideString = false;

  if ( EndStringPos == wxNOT_FOUND )
    Line.Clear();
  else if ( EndStringPos > 0 )
  {
    if ( Line.GetChar(EndStringPos-1) == '\\' )

      Line.Remove(0,EndStringPos+1);
    else
      OutsideString = true;
  }
  else
      OutsideString = true;

  if ( OutsideString )
    Line.Remove(0,EndStringPos+1);

  return !OutsideString;
}
