lookfor ( char *pattern )
{
 FILE *fp ;
 char fname[127];
 char buf[80];
 char sbuf[80];
 byte car ;

    StrLwr( pattern );
    car = equival (pattern[0]);


    sprintf(fname, "%s%s%c%s", dict_path, sep, car, DICT_EXT ) ;

    if(( fp = fopen(fname,"r")) == NULL )
    {
        fprintf(stderr,"Impossible de lire fichier %s\n", fname );
        file_usage();
        return ;
    }

#ifdef MUST_HAVE_BUF
    setvbuf( fp, NULL, _IOFBF, MYVBUF );
#endif

    StrAscii( pattern);
    while( fgets(buf,79,fp) )
    {
        if( *buf == '#' )
            continue ;
        nolf( buf );
        strcpy( sbuf, buf );
        StrAscii( sbuf);
        if( fmatch(sbuf,pattern) )
        {
            translate( buf );
            printf("\t%s\n",conversion_charset (beautify(buf),"ISO-8859-1",charset)  );
            count ++ ;
        }
    }

    fclose( fp) ;
}
