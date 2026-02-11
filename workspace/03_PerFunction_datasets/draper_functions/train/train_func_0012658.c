transportDec_Close(HANDLE_TRANSPORTDEC *phTp)
{
  if (phTp != NULL)
  {
    if (*phTp != NULL) {
      if ((*phTp)->transportFmt != TT_MP4_RAW && (*phTp)->transportFmt != TT_DRM) {
        FreeRam_TransportDecoderBuffer(&(*phTp)->bsBuffer);
      }
      if (*phTp != NULL) {
        FreeRam_TransportDecoder(phTp);
      }
    }
  }
}
