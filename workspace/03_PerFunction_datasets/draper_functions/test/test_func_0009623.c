get()
{
    int ch = -1;
    if (closed) {

    }
    else if (!loaded && !load()) {
        closed=true;
    } else {
        loaded = true;

        int zerr = Z_OK;
        if ( outputBufPos >= outputBufLen ) {

            zerr = fetchMore();
        }

        if ( outputBufPos < outputBufLen ) {
            ch = (int)outputBuf[outputBufPos++];
        }
    }

    return ch;
}
