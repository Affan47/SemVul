maker_toshiba_tagname(unsigned short tag,int model)
{
    char *tagname = CNULL;

#if 0
    int noteversion = 0;

    if((noteversion = getnoteversion()) == 0)
    {
        noteversion = 1;
        setnoteversion(1);
    }

    switch(noteversion)
    {
        case 1:
            tagname = maker_toshiba1_tagname(tag,model);
        default:
            break;
    }
#endif


    if(tagname == NULL)
    {
        switch(tag)
        {
            case 0x0e00: tagname = "PrintIM"; break;
            default: break;
        }
    }
    return(tagname);
}
