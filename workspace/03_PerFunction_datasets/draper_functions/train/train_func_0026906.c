readPgfHeaderStructure(BasicIo& iIo, int* width, int* height)
    {
        DataBuf header(16);
        long bufRead = iIo.read(header.pData_, header.size_);
        if (iIo.error()) throw Error(14);
        if (bufRead != header.size_) throw Error(20);

        memcpy(width,  &header.pData_[0], 4);
        memcpy(height, &header.pData_[4], 4);


        byte mode     = header.pData_[12];

        if (mode == 2)
        {
            header.alloc(16 + 256*3);

            bufRead = iIo.read(&header.pData_[16], 256*3);
            if (iIo.error()) throw Error(14);
            if (bufRead != 256*3) throw Error(20);
        }

        return header;
    }
