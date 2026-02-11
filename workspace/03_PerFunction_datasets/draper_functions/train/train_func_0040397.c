parse_filemode (const char *p)
{
    int res = 0;

    switch (*(p++)){
    case 'r': res |= 0400; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'w': res |= 0200; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'x': res |= 0100; break;
    case 's': res |= 0100 | AV_ISUID; break;
    case 'S': res |= AV_ISUID; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'r': res |= 0040; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'w': res |= 0020; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'x': res |= 0010; break;
    case 's': res |= 0010 | AV_ISGID; break;
    case 'S': res |= AV_ISGID; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'r': res |= 0004; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'w': res |= 0002; break;
    case '-': break;
    default: return -1;
    }

    switch (*(p++)){
    case 'x': res |= 0001; break;
    case 't': res |= 0001 | AV_ISVTX; break;
    case 'T': res |= AV_ISVTX; break;
    case '-': break;
    default: return -1;
    }

    return res;
}
