WriteSubTree(const wxString &value)
{
   if (mInTag) {
      Write(wxT(">\n"));
      mInTag = false;
      mHasKids[0] = true;
   }

   Write(value.c_str());
}
