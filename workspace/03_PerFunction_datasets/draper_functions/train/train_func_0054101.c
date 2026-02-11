init ( const char            * file,
                    unsigned int            line,
                    const char            * description  = 0,
                    int                     code         = 0 )  throw ()
{
    if ( !file ) {
        this->file = 0;
    } else {
        size_t  len;

        len        = strlen( file ) + 1;
        this->file = new char[len];
        if ( this->file ) {
            memcpy( this->file, file, len);
        }
    }

    if ( !description ) {
        this->description = 0;
    } else {
        size_t  len;

        len               = strlen( description ) + 1;
        this->description = new char[len];
        if ( this->description ) {
            memcpy( this->description, description, len);
        }
    }

    this->line = line;
    this->code = code;
}
