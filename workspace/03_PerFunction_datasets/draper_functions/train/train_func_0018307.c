split( const String& str, const String& delims, unsigned int maxSplits, bool preserveDelims)
    {
        StringVector ret;

        ret.reserve(maxSplits ? maxSplits+1 : 10);

        unsigned int numSplits = 0;


        size_t start, pos;
        start = 0;
        do
        {
            pos = str.find_first_of(delims, start);
            if (pos == start)
            {

                start = pos + 1;
            }
            else if (pos == String::npos || (maxSplits && numSplits == maxSplits))
            {

                ret.push_back( str.substr(start) );
                break;
            }
            else
            {

                ret.push_back( str.substr(start, pos - start) );

                if(preserveDelims)
                {


                    size_t delimStart = pos, delimPos;
                    delimPos = str.find_first_not_of(delims, delimStart);
                    if (delimPos == String::npos)
                    {

                        ret.push_back( str.substr(delimStart) );
                    }
                    else
                    {
                        ret.push_back( str.substr(delimStart, delimPos - delimStart) );
                    }
                }

                start = pos + 1;
            }

            start = str.find_first_not_of(delims, start);
            ++numSplits;

        } while (pos != String::npos);


        return ret;
    }
