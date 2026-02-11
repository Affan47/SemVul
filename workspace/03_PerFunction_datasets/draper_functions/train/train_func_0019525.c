alma_in_sequence()  {

    char         temp[LINENUM];
    FILE        *IFP;
    FILE_BUFFER  ifp;

    if((IFP=fopen(data.alma.filename, "r"))==NULL) {
        sprintf(temp, "Cannot open file %s, Exit.", data.alma.filename);
        error(51, temp);
    }

    ifp = create_FILE_BUFFER(data.alma.filename, IFP);

    if(data.alma.format==NBRF)  {
        nbrf_in(ifp);
    } else if(data.alma.format==GCG)    {
        gcg_in(ifp);
    } else if(data.alma.format==EMBL)   {
        init_embl();
        embl_in(ifp);
    } else if(data.alma.format==STADEN) {
        staden_in(ifp);
    } else {
        sprintf(temp, "Unidentified file format %d in ALMA file, Exit.", data.alma.format);
        error(50, temp);
    }
    destroy_FILE_BUFFER(ifp);
}
