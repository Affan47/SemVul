cleanup()
{
  if (registered)
  {
    DcmCodecList::deregisterCodec(codec);
    delete codec;
    delete cp;
    registered = OFFalse;
#ifdef DEBUG

    codec = NULL;
    cp     = NULL;
#endif

  }
}
