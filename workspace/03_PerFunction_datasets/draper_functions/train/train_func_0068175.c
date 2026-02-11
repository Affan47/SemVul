frame_buffercheck(mpg123_handle *fr)
{

	if(!fr->accurate) return;


	if(fr->firstoff && fr->num == fr->firstframe)
	{
		off_t byteoff = samples_to_bytes(fr, fr->firstoff);
		if((off_t)fr->buffer.fill > byteoff)
		{
			fr->buffer.fill -= byteoff;

			debug6("cutting %li samples/%li bytes on begin, own_buffer=%i at %p=%p, buf[1]=%i",
			        (long)fr->firstoff, (long)byteoff, fr->own_buffer, (void*)fr->buffer.p, (void*)fr->buffer.data, ((short*)fr->buffer.p)[2]);
			if(fr->own_buffer) fr->buffer.p = fr->buffer.data + byteoff;
			else memmove(fr->buffer.data, fr->buffer.data + byteoff, fr->buffer.fill);
			debug3("done cutting, buffer at %p =? %p, buf[1]=%i",
			        (void*)fr->buffer.p, (void*)fr->buffer.data, ((short*)fr->buffer.p)[2]);
		}
		else fr->buffer.fill = 0;


		fr->firstoff = 0;
	}


	if(fr->lastoff && fr->num == fr->lastframe)
	{
		off_t byteoff = samples_to_bytes(fr, fr->lastoff);
		if((off_t)fr->buffer.fill > byteoff)
		{
			fr->buffer.fill = byteoff;
		}
	}
}
