save(ofstream & fp) const
    {
        uint type = ALPHPART_HDR;
        saveValue(fp,type);
        saveValue(fp,sigma);
        saveValue(fp,origsigma);
        saveValue(fp,maxLen);
        saveValue(fp,cut);
        saveValue(fp,revPermFreq,sigma+1);
        saveValue(fp,alphSortedByFreq,sigma+1);
        groupsIndex->save(fp);
        for(uint i=0;maxLen>cut && i<maxLen-cut;i++)
            indexesByLength[i]->save(fp);
    }
