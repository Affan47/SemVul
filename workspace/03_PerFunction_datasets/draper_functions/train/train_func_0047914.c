StartTag(const wxString &name)
{
   int i;

   if (mInTag) {
      Write(wxT(">\n"));
      mInTag = false;
   }

   for (i = 0; i < mDepth; i++) {
      Write(wxT("\t"));
   }

   Write(wxString::Format(wxT("<%s"), name.c_str()));

   mTagstack.Insert(name, 0);
   mHasKids[0] = true;
   mHasKids.Insert(false, 0);
   mDepth++;
   mInTag = true;
}
