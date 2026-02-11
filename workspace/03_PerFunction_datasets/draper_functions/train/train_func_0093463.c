process_data (PROCDATA_HANDLE *ph, unsigned char *read_ptr, int nread)

{int bytes_left;
 HpProcessData *procdata;

 if (nread <= 0) return SANE_STATUS_GOOD;

 if (ph == NULL) return SANE_STATUS_INVAL;

 procdata = &(ph->procdata);
 if ( ph->tmp_buf_len > 0 )
 {
   bytes_left = ph->tmp_buf_size - ph->tmp_buf_len;
   if (nread < bytes_left)
   {
     memcpy (ph->tmp_buf+ph->tmp_buf_len, read_ptr, nread);
     ph->tmp_buf_len += nread;
     return SANE_STATUS_GOOD;
   }
   memcpy (ph->tmp_buf+ph->tmp_buf_len, read_ptr, bytes_left);
   read_ptr += bytes_left;
   nread -= bytes_left;
   RETURN_IF_FAIL ( process_scanline (ph, ph->tmp_buf, ph->tmp_buf_size) );
   ph->tmp_buf_len = 0;
 }
 while (nread > 0)
 {
   if (nread >= ph->tmp_buf_size)
   {
     RETURN_IF_FAIL ( process_scanline (ph, read_ptr, ph->tmp_buf_size) );
     read_ptr += ph->tmp_buf_size;
     nread -= ph->tmp_buf_size;
   }
   else
   {
     memcpy (ph->tmp_buf, read_ptr, nread);
     ph->tmp_buf_len = nread;
     nread = 0;
   }
 }
 return SANE_STATUS_GOOD;
}
