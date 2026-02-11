seqPrefixGenbankMore(const AjPStr str)
{
    SeqEPrefixGenbankMore imore = GB_MORE_UNK;
    const char* cp = MAJSTRGETPTR(str);
    const char* cq = (cp+1);
    const char* cr = (cp+1);

    if(*cp != ' ' || *cq != ' ')
        return GB_MORE_STD;

    switch (*cr)
    {
        case 'A':
            if(!strncmp(cr, "AUTHORS",7)) imore = GB_MORE_AUT;
            break;
        case 'B':
            break;
        case 'C':
            break;
        case 'D':
            break;
        case 'F':
            break;
        case 'J':
            if(!strncmp(cr, "JOURNAL",7)) imore = GB_MORE_JNL;
            break;
        case 'O':
            if(!strncmp(cr, "ORGANISM",8)) imore = GB_MORE_ORG;
            break;
        case 'T':
            break;
            if(!strncmp(cr, "TITLE",5)) imore = GB_MORE_TIT;
        case 'W':
            break;
        case '/':
            break;
        case ' ':
            if(!strncmp(cr, "        ",8)) imore = GB_MORE_MORE;
            break;
        default:
            imore = GB_MORE_UNK;
            break;
    }

    return imore;
}
