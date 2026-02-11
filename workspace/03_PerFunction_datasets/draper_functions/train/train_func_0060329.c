next()
{
   errmsg = NULL;
   if (beg <= end) {
      return beg++;
   }
   if (e == NULL) {
      goto bail_out;
   }


   for (p=e; p && *p; p=e) {

      e = strchr(p, ',');
      if (e) {
         esave = *e;
         *e++ = 0;
      } else {
         esave = 0;
      }

      h = strchr(p, '-');
      if (h == p) {
         errmsg = _("Negative numbers not permitted.\n");
         goto bail_out;
      }
      if (h) {
         hsave = *h;
         *h++ = 0;
         if (!is_an_integer(h)) {
            errmsg = _("Range end is not integer.\n");
            goto bail_out;
         }
         skip_spaces(&p);
         if (!is_an_integer(p)) {
            errmsg = _("Range start is not an integer.\n");
            goto bail_out;
         }
         beg = str_to_int64(p);
         end = str_to_int64(h);
         if (end < beg) {
            errmsg = _("Range end not bigger than start.\n");
            goto bail_out;
         }
      } else {
         hsave = 0;
         skip_spaces(&p);
         if (!is_an_integer(p)) {
            errmsg = _("Input value is not an integer.\n");
            goto bail_out;
         }
         beg = end = str_to_int64(p);
      }
      if (esave) {
         *(e-1) = esave;
      }
      if (hsave) {
         *(h-1) = hsave;
      }
      if (beg <= 0 || end <= 0) {
         errmsg = _("Selection items must be be greater than zero.\n");
         goto bail_out;
      }
      if (end > max) {
         errmsg = _("Selection item too large.\n");
         goto bail_out;
      }
      if (beg <= end) {
         return beg++;
      }
   }

   errmsg = NULL;
   return -1;

bail_out:
   return -1;
}
