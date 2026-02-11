Read(istream* pIndexstream)
  {


    if(!ReadHeader(pIndexstream))
      {
        *(header.datafilename) = '\0';
        return false;
      }

    unsigned int nwords = header.nEntries * header.words;
    fptdata.resize(nwords);
    seekdata.resize(header.nEntries);

    pIndexstream->read((char*)&(fptdata[0]), sizeof(unsigned int) * nwords);
    pIndexstream->read((char*)&(seekdata[0]), sizeof(unsigned int) * header.nEntries);

    if(pIndexstream->fail())
      {
        *(header.datafilename) = '\0';
        return false;
      }
    return true;
  }
