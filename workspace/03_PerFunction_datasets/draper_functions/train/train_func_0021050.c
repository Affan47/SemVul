aacDecoder_SignalInterruption(HANDLE_AACDECODER self)
{
  CAacDecoder_SignalInterruption(self);

  if ( self->hSbrDecoder != NULL ) {
    sbrDecoder_SetParam(self->hSbrDecoder, SBR_BS_INTERRUPTION, 0);
  }
}
