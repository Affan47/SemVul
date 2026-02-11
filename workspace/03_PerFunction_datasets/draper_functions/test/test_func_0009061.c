FormatSize(double size)
{
   wxString sizeStr;

   if (size == -1)
      sizeStr = _("Unable to determine");
   else {

      if (size < 1024.0)
         sizeStr = ToDisplayString(size) + wxT(" ") + _("bytes");
      else if (size < 1024.0 * 1024.0) {

         sizeStr = ToDisplayString(size / 1024.0, 1) + wxT(" ") + _("KB");
      }
      else if (size < 1024.0 * 1024.0 * 1024.0) {

         sizeStr = ToDisplayString(size / (1024.0 * 1024.0), 1) + wxT(" ") + _("MB");
      }
      else {

         sizeStr = ToDisplayString(size / (1024.0 * 1024.0 * 1024.0), 1) + wxT(" ") + _("GB");
      }
   }

   return sizeStr;
}
