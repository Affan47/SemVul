LoadSamples(progress_t* pProgress) {


        if (!pGroups) LoadGroups();

        if (!pSamples) pSamples = new SampleList;

        RIFF::File* file = pRIFF;


        int iSampleIndex  = 0;
        int iTotalSamples = WavePoolCount;


        int lastFileNo = 0;
        for (int i = 0 ; i < WavePoolCount ; i++) {
            if (pWavePoolTableHi[i] > lastFileNo) lastFileNo = pWavePoolTableHi[i];
        }
        String name(pRIFF->GetFileName());
        int nameLen = name.length();
        char suffix[6];
        if (nameLen > 4 && name.substr(nameLen - 4) == ".gig") nameLen -= 4;

        for (int fileNo = 0 ; ; ) {
            RIFF::List* wvpl = file->GetSubList(LIST_TYPE_WVPL);
            if (wvpl) {
                unsigned long wvplFileOffset = wvpl->GetFilePos();
                RIFF::List* wave = wvpl->GetFirstSubList();
                while (wave) {
                    if (wave->GetListType() == LIST_TYPE_WAVE) {

                        const float subprogress = (float) iSampleIndex / (float) iTotalSamples;
                        __notify_progress(pProgress, subprogress);

                        unsigned long waveFileOffset = wave->GetFilePos();
                        pSamples->push_back(new Sample(this, wave, waveFileOffset - wvplFileOffset, fileNo));

                        iSampleIndex++;
                    }
                    wave = wvpl->GetNextSubList();
                }

                if (fileNo == lastFileNo) break;


                fileNo++;
                sprintf(suffix, ".gx%02d", fileNo);
                name.replace(nameLen, 5, suffix);
                file = new RIFF::File(name);
                ExtensionFiles.push_back(file);
            } else break;
        }

        __notify_progress(pProgress, 1.0);
    }
