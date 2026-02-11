canon_customfunctions(FILE *inptr,unsigned short byteorder,
    char *tagprefix,unsigned long offset,
    unsigned long dirlength,int model,int indent)
{
    unsigned long max_offset;
    int noteversion = 0;

    noteversion = getnoteversion();

    switch(noteversion)
    {
    case 5:
        max_offset = canon_customfunctions1D(inptr,byteorder,tagprefix,offset,dirlength,indent);
        break;
    case 4:
        max_offset = canon_customfunctions20D(inptr,byteorder,tagprefix,offset,dirlength,indent);
        break;
    case 3:
        max_offset = canon_customfunctions10D(inptr,byteorder,tagprefix,offset,dirlength,indent);
        break;
    case 2:
        max_offset = canon_customfunctionsD30(inptr,byteorder,tagprefix,offset,dirlength,indent);
        break;
    case 1:
    default:
        max_offset = canon_customfunctions_unk(inptr,byteorder,tagprefix,offset,dirlength,indent);
        break;
    }
    return(max_offset);
}
