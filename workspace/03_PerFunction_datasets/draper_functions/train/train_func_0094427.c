underflow() {
    if ( gptr() && ( gptr() < egptr()))
        return * reinterpret_cast<unsigned char *>( gptr());

    if ( ! (mode & ios::in) || ! opened)
        return EOF;

    int n_putback = gptr() - eback();
    if ( n_putback > 4)
        n_putback = 4;
    memcpy( buffer + (4 - n_putback), gptr() - n_putback, n_putback);

    int num = gzread( file, buffer+4, bufferSize-4);
    if (num <= 0)
        return EOF;


    setg( buffer + (4 - n_putback),
          buffer + 4,
          buffer + 4 + num);


    return * reinterpret_cast<unsigned char *>( gptr());
}
