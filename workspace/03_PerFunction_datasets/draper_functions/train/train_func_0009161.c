LoadSweepData (BYTE *imagedata, int imagesize)
{
    UInt16 mem_needed = SIZEOF_LDLHDR + SIZEOF_LDL_LDSWPDATA_CMDOPT
                                      + SIZEOF_LDLTERM;
    UInt16 diff=0;
    if(mem_needed < LDLPACKET_MINSIZE)
    {
        diff = LDLPACKET_MINSIZE - mem_needed;
        mem_needed = LDLPACKET_MINSIZE;
    }
    memset (m_szCmdBuf, 0, mem_needed);

    BYTE    *compressed_dataptr = imagedata;
    UInt16  compressed_size = imagesize;

#ifdef  APDK_LDL_COMPRESS
    if (m_ldlCompressData)
    {
  	    m_ldlCompressData->Init ((UInt16 *) (imagedata+16), imagesize);
	    CompressData ();
	    GetFrameInfo (&compressed_dataptr, &compressed_size);
    }
#endif

    FillLidilHeader (NULL, eLDLLoadSweepData, mem_needed, compressed_size);

    int     index = SIZEOF_LDLHDR;
    WRITE16 (imagesize);

    if(diff)
    {
        memset (m_szCmdBuf+index, 0xFF, diff);
        index += diff;
    }
    m_szCmdBuf[index++] = FRAME_SYN;

    memcpy (compressed_dataptr, m_szCmdBuf, 16);
    return (pPrinterXBow->Send (compressed_dataptr, (DWORD) compressed_size+16));
}
