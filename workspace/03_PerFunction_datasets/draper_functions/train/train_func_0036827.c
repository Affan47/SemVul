_eina_simple_xml_whitespace_unskip(const char *itr, const char *itr_start)
{
   for (itr--; itr > itr_start; itr--)
     if (!isspace((unsigned char)*itr)) break;
   return itr + 1;
}
