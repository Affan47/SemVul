has_data(int dstart, int dlength)
{
   if (dlength<0 && length>0)
     dlength=length-dstart;
   return (pool?(pool->has_data(start+dstart, dlength))
     :((furl.is_local_file_url())?(start+dstart+dlength<=length)
       :((dlength<0)?is_eof()
         :(block_list->get_bytes(dstart, dlength)==dlength))));
}
