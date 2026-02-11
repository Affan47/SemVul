readRequest()
{


    struct timeval start_of_idle;
    gettimeofday(&start_of_idle, NULL);


    bool query_started = false;


    char *r = _read_pointer;

    while (true)
    {

        while (r < _write_pointer && r[0] != '\n')
            r++;


        if (r == _write_pointer)
        {


            if (_write_pointer < _end_pointer)
            {
                int rd = readData();
                if (rd == IB_TIMEOUT) {
                    if (query_started) {
                        logger(LG_INFO, "Timeout of %d ms exceeded while reading query", g_query_timeout_msec);
                        return IB_TIMEOUT;
                    }

                    else if (timeout_reached(&start_of_idle, g_idle_timeout_msec)) {
                        logger(LG_INFO, "Idle timeout of %d ms exceeded. Going to close connection.", g_idle_timeout_msec);
                        return IB_TIMEOUT;
                    }
                }


                else if (rd == IB_END_OF_FILE && r == _read_pointer )
                {
                    if (_requestlines.empty()) {
                        return IB_END_OF_FILE;
                    }
                    else {

                        return IB_REQUEST_READ;


                    }
                }


                else if (rd == IB_END_OF_FILE)
                    return IB_UNEXPECTED_END_OF_FILE;


                else if (rd == IB_SHOULD_TERMINATE)
                    return rd;
            }


            else if (_read_pointer > _readahead_buffer) {
                int shift_by = _read_pointer - _readahead_buffer;
                int size     = _write_pointer - _read_pointer;
                memmove(_readahead_buffer, _read_pointer, size);
                _read_pointer = _readahead_buffer;
                _write_pointer -= shift_by;
                r -= shift_by;


            }

            else {
                logger(LG_INFO, "Error: maximum length of request line exceeded");
                return IB_LINE_TOO_LONG;
            }
        }
        else
        {
            if (_read_pointer == r) {
                _read_pointer = r + 1;

                if (_requestlines.size() == 0) {
                    return IB_EMPTY_REQUEST;
                }
                else
                    return IB_REQUEST_READ;
            }
            else {
                storeRequestLine(_read_pointer, r - _read_pointer);
                query_started = true;
                _read_pointer = r + 1;
                r = _read_pointer;
            }
        }
    }
}
