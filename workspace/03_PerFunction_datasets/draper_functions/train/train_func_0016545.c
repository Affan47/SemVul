owTest()
{
  uint8_t nOwMem = 0;
  uint8_t nOwIter = 0;
  OwSerialNum sn;

  if (owScan(&nOwMem))
  {
    DEBUG_PRINT("Found %d.\n", nOwMem);
  }
  else
  {
    DEBUG_PRINT("Scan [FAILED].\n");
  }

  for (nOwIter = 0; nOwIter < nOwMem; nOwIter++)
  {
    if (owGetinfo(nOwIter, &sn))
    {
      DEBUG_PRINT("Serial 0x%X %X %X %X %X %X %X %X.\n",
                  sn.type, sn.id[0], sn.id[1], sn.id[2],
                  sn.id[3], sn.id[4], sn.id[5], sn.crc);
    }
    else
    {
      DEBUG_PRINT("Mem:%d Getinfo [FAILED].\n", nOwIter);
    }
  }

#ifdef OW_READ_TEST
  {
    static uint8_t testbuf[129];

    if (owRead(0, 0, OW_MAX_SIZE, testbuf))
    {
      for (nOwIter = 0; nOwIter < OW_MAX_SIZE; nOwIter++)
      {
        consolePrintf("%X ", testbuf[nOwIter]);
        testbuf[nOwIter] = nOwIter;
      }
      consolePrintf("\n");
    }
  }
#endif
#ifdef OW_WRITE_TEST
  if (owWrite(0, 0, sizeof(bqtestData), bqtestData))
  {
    DEBUG_PRINT("Write [OK].\n");
  }
  else
  {
    DEBUG_PRINT("Write [FAIL].\n");
  }
#endif

  return true;
}
