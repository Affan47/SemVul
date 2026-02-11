read(void *buffer, size_t frame_count)
{
   size_t read_size;

   if (!this->good)
      return -1;

   read_size = MIN(frame_count, this->data_left);
   if (read_size == 0)
      return 0;

   if (this->bytes == 2)
   {
      int16_t *buf = static_cast<int16_t *>(buffer);
      int16_t *p;

      for (size_t n = 0; n < read_size; n++)
      {
	 for (int c = 0; c < this->chans; c++)
	 {
	    p = &buf[n * this->chans + c];

	    if (!read_le<int16_t>(this->in, p))
	    {
	       this->good = false;
	       return n;
	    }
	 }
      }
   }
   else if (this->bytes == 1)
   {
      if (!this->in->read(buffer, this->chans * read_size))
      {
	 this->good = false;
	 return 0;
      }
   }
   else
      abort();

   this->data_left -= read_size;

   return read_size;
}
