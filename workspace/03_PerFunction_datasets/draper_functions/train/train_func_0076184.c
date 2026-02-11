aacDecoder_ConfigCallback(void *handle, const CSAudioSpecificConfig *pAscStruct)
{
  HANDLE_AACDECODER self = (HANDLE_AACDECODER)handle;
  AAC_DECODER_ERROR err = AAC_DEC_OK;
  TRANSPORTDEC_ERROR errTp;

  {
    {
      err = aacDecoder_Config(self, pAscStruct);
    }
  }
  if (err == AAC_DEC_OK) {
    if ( self->flags & (AC_USAC|AC_RSVD50|AC_LD|AC_ELD)
      && CConcealment_GetDelay(&self->concealCommonData) > 0 )
    {


      setConcealMethod(self, 1);
#ifdef DEBUG
      FDKprintf("  Concealment method was reverted to 1 !\n");
#endif
    }
    errTp = TRANSPORTDEC_OK;
  } else {
    if (IS_INIT_ERROR(err)) {
      errTp = TRANSPORTDEC_UNSUPPORTED_FORMAT;
    }
    else if (err == AAC_DEC_NEED_TO_RESTART) {
      errTp = TRANSPORTDEC_NEED_TO_RESTART;
    } else {
      errTp = TRANSPORTDEC_UNKOWN_ERROR;
    }
  }

  return errTp;
}
