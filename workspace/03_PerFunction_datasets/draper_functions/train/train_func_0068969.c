Restart()
{
    nNextRaster = 0;

    for (unsigned int i = StartPlane; i <= EndPlane; i++)
      {
        memset(ErrBuff[i], 0, (OutputWidth[i]+2) * sizeof(short));
      }

    started = FALSE;
}
