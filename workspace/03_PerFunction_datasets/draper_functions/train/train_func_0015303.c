sbrEncoder_GetHeader(SBR_ENCODER   *sbrEncoder,
                          HANDLE_FDK_BITSTREAM hBs,
                          INT            element_index,
                          int            fSendHeaders)
{
  int bits;

  bits = encodeSbrHeaderData (&sbrEncoder->sbrElement[element_index]->sbrHeaderData, hBs);

  if (fSendHeaders == 0) {

    sbrEncoder->sbrElement[element_index]->sbrBitstreamData.NrSendHeaderData = -1;
    sbrEncoder->sbrElement[element_index]->sbrBitstreamData.HeaderActive = 0;
    sbrEncoder->sbrElement[element_index]->sbrBitstreamData.CountSendHeaderData = -1;
  }
}
