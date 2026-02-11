ReadLine(std::istream &s, bool enableEscapeSequences ){
    char c=' ';
    int i=0;
    SetLen(0);


    while(c!='\n' && c!='\r' && isblank(c) &&  s.good() && !s.eof()){
        c=s.get();
    }
    if(s.good())
    {
        s.putback(c);
    }

    c='x';

    while( true )
    {
        c=s.get();


        if ( c=='\n' || c=='\r' || !s.good() || s.eof())
            break;

        if ( enableEscapeSequences )
        {
            char c2 = '\0';
            if ( st_ReadEscapeSequence( c, c2, s ) )
            {
                operator[](i++)=c;
                c = 'x';
                continue;
            }
            else if ( c2 )
            {
                operator[](i++)=c;
                operator[](i++)=c2;
                c = 'x';
                continue;
            }
        }
        operator[](i++)=c;
    }

    operator[](i)='\0';
}
