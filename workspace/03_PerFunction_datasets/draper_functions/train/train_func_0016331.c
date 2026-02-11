cl_com_get_h_error_string(int h_error) {

   if (h_error == HOST_NOT_FOUND) {
      return strdup("h_errno = HOST_NOT_FOUND");
   } else if (h_error == TRY_AGAIN) {
      return strdup("h_errno = TRY_AGAIN");
   } else if (h_error == NO_RECOVERY) {
      return strdup("h_errno = NO_RECOVERY");
   } else if (NO_DATA == NO_ADDRESS && h_error == NO_DATA) {
      return strdup("h_errno = NO_DATA or NO_ADDRESS");
   } else if (h_error == NO_DATA) {
      return strdup("h_errno = NO_DATA");
   } else if (h_error == NO_ADDRESS) {
      return strdup("h_errno = NO_ADDRESS");
   }
   return NULL;
}
