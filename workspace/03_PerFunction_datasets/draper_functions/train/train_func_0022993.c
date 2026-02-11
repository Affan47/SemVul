LoadMem(ByteBuffer& buf)
{
    uint8 *fourcc = new uint8[5];
    fourcc[4] = 0;
    uint32 size;

    while(buf.rpos() < buf.size())
    {
        buf.read(fourcc,4); flipcc(fourcc);
        buf >> size;

        if(!strcmp((char*)fourcc,"MVER"))
        {
            _mver = buf.read<WDT_MVER_Chunk>();
        }
        else if(!strcmp((char*)fourcc,"MPHD"))
        {
            _mphd = buf.read<WDT_MPHD_Chunk>();
        }
        else if(!strcmp((char*)fourcc,"MAIN"))
        {
            _main = buf.read<WDT_MAIN_Chunk>();
        }
        else if(!strcmp((char*)fourcc,"MWMO"))
        {
            if(size)
            {
                DEBUG(printf("WDTFile::LoadMem() abort load, MWMO block isnt empty\n"));
                break;
            }
        }
        else if(!strcmp((char*)fourcc,"MODF"))
        {
            DEBUG(printf("WDTFile::LoadMem() abort load, MODF block exists\n"));
            break;
        }
    }
    delete [] fourcc;
    return true;
}
