AddInstrument() {
       if (!pInstruments) LoadInstruments();
       __ensureMandatoryChunksExist();
       RIFF::List* lstInstruments = pRIFF->GetSubList(LIST_TYPE_LINS);
       RIFF::List* lstInstr = lstInstruments->AddSubList(LIST_TYPE_INS);


       lstInstr->AddSubList(LIST_TYPE_INFO);
       lstInstr->AddSubChunk(CHUNK_ID_DLID, 16);

       Instrument* pInstrument = new Instrument(this, lstInstr);
       pInstrument->GenerateDLSID();

       lstInstr->AddSubChunk(CHUNK_ID_INSH, 12);


       pInstrument->pInfo->Software = "Endless Wave";

       pInstruments->push_back(pInstrument);
       return pInstrument;
    }
