tag_exists(const char *tag, const char **tags)
{
    int itag=0;
    if ( !tags ) return -1;
    while ( tags[itag] )
    {
        if ( tags[itag][0]==tag[0] && tags[itag][1]==tag[1] ) return itag;
        itag++;
    }
    return -1;
}
