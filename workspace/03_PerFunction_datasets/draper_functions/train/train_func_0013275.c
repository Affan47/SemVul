nextPosition ()
{
  if (_in_range)
    {

      if (++_range_curr_value >= _range_upper_bound)
        _in_range = false;
      return _range_curr_value;
    }
  else
    {

      while (*_str)
        switch (*_str)
          {
          case ',':

            _str++;
            break;
          case '$':

            _str++;
            return _end_word_marker;
          case '0': case '1': case '2': case '3': case '4':
          case '5': case '6': case '7': case '8': case '9':

            {
              int curr_value;
              for (curr_value = 0; isdigit (static_cast<unsigned char>(*_str)); _str++)
                curr_value = curr_value * 10 + (*_str - '0');

              if (*_str == '-')
                {
                  _str++;

                  _in_range = true;

                  for (_range_upper_bound = 0;
                       isdigit (static_cast<unsigned char>(*_str));
                       _str++)
                    _range_upper_bound = _range_upper_bound * 10 + (*_str - '0');


                  if (!(_range_upper_bound > curr_value && _range_upper_bound <= _high_bound))
                    return _error_value;
                  _range_curr_value = curr_value;
                }


              if (!(curr_value >= _low_bound && curr_value <= _high_bound))
                return _error_value;
              return curr_value;
            }
          default:

            return _error_value;
          }

      return _end_marker;
    }
}
