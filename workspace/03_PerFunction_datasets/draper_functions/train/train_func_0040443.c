OnToggle(wxCommandEvent & WXUNUSED(event))
{
   if (mIsExpanded)
      Collapse();
   else
      Expand();
}
