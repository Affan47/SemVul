set( int line, int column )
{
    if ( ( line_ == -1 ) ||
            ( ( line <= line_ ) && ( column < column_ ) ) )
    {
        line_ = line;
        column_ = column;
    }
}
