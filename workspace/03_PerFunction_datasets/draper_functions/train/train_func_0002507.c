jpeg_memio_dest (j_compress_ptr cinfo, guchar *memjpeg, size_t **remaining)
{
   memjpeg_dest_mgr *dest;


  if (cinfo->dest == NULL)
    {
      cinfo->dest = (struct jpeg_destination_mgr *)
        (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                    sizeof(memjpeg_dest_mgr));
    }

  dest = (memjpeg_dest_mgr *) cinfo->dest;
  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;
  dest->buffer = memjpeg;
  *remaining = &(dest->pub.free_in_buffer);
}
