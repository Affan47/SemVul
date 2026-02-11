init()
{
  suspension = 0;
  decompressedColorModel = EPI_Unknown;
  cleanup();

  cinfo = new jpeg_decompress_struct();
  if (cinfo)
  {
    volatile DJDIJG12SourceManagerStruct *src = NULL;
    volatile DJDIJG12ErrorStruct *jerr = new DJDIJG12ErrorStruct();
    if (jerr)
    {
      src = new DJDIJG12SourceManagerStruct();
      if (src)
      {

        src->pub.init_source       = DJDIJG12initSource;
        src->pub.fill_input_buffer = DJDIJG12fillInputBuffer;
        src->pub.skip_input_data   = DJDIJG12skipInputData;
        src->pub.resync_to_restart = jpeg_resync_to_restart;
        src->pub.term_source       = DJDIJG12termSource;
        src->pub.bytes_in_buffer   = 0;
        src->pub.next_input_byte   = NULL;
        src->skip_bytes             = 0;
        src->next_buffer            = NULL;
        src->next_buffer_size       = 0;
      }
      else
      {
        delete OFconst_cast(DJDIJG12ErrorStruct *, jerr);
        delete cinfo;
        cinfo = NULL;
        return EC_MemoryExhausted;
      }
      cinfo->err = jpeg_std_error(& OFconst_cast(DJDIJG12ErrorStruct *, jerr)->pub);
      jerr->instance = this;
      jerr->pub.error_exit = DJDIJG12ErrorExit;
      jerr->pub.emit_message = DJDIJG12EmitMessage;
      if (setjmp(OFconst_cast(DJDIJG12ErrorStruct *, jerr)->setjmp_buffer))
      {

        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message)((jpeg_common_struct *)cinfo, buffer);
        cleanup();
        return makeOFCondition(OFM_dcmjpeg, EJCode_IJG12_Decompression, OF_error, buffer);
      }
    }
    else
    {
      delete cinfo;
      cinfo = NULL;
      return EC_MemoryExhausted;
    }
    jpeg_create_decompress(cinfo);
    cinfo->src = &OFconst_cast(DJDIJG12SourceManagerStruct *, src)->pub;
  } else return EC_MemoryExhausted;


  return EC_Normal;
}
