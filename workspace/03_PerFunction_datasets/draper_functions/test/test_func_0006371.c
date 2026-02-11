advance()
    {
        if( eof() )
            mPeek = "" ;
        else
            mIn >> mPeek >> std::ws ;
    }
