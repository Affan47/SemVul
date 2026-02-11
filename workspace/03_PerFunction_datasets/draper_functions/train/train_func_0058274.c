_dxf_RemoveImageExtension(char *name, ImageType type)
{
    int i;


    for ( i = strlen (name) - 1; i >= 0; i-- )
        if (name[i] == '/')
            return;
        else if (name[i] == '.')
            break;


    if ( ValidImageExtension(&name[i+1],type) )
        name[i] = '\0';
}
