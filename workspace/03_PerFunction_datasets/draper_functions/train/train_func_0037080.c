ar_get_type_string(char *buf, size_t buflen, u_long32 type)
{
   if (type != 0) {
      snprintf(buf, buflen-1, "-now");
   } else {
      strcat(buf, "");
   }
}
