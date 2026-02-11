get_page_size_str(char *buffer,size_t len,m_uint32_t page_mask)
{
   m_uint32_t page_size;

   page_size = get_page_size(page_mask);


   if (page_size >= (1024*1024))
      snprintf(buffer,len,"%uMB",page_size >> 20);
   else
      snprintf(buffer,len,"%uKB",page_size >> 10);

   return buffer;
}
