EndTag(const wxString &name)
{
   int i;

   if (mTagstack.GetCount() > 0) {
      if (mTagstack[0] == name) {
         if (mHasKids[1]) {
            if (mInTag) {
               Write(wxT("/>\n"));
            }
            else {
               for (i = 0; i < mDepth - 1; i++) {
                  Write(wxT("\t"));
               }
               Write(wxString::Format(wxT("</%s>\n"), name.c_str()));
            }
         }
         else {
            Write(wxT(">\n"));
         }
         mTagstack.RemoveAt(0);
         mHasKids.RemoveAt(0);
      }
   }

   mDepth--;
   mInTag = false;
}
