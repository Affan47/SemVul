logEvent(const String& message, LoggingLevel level )
    {
        using namespace std;

        time_t  et;
        time(&et);
        tm* etm = localtime(&et);

        if (etm)
        {

            d_workstream.str("");


            d_workstream << setfill('0') << setw(2) << etm->tm_mday << '/' <<
            setfill('0') << setw(2) << 1 + etm->tm_mon << '/' <<
            setw(4) << (1900 + etm->tm_year) << ' ';


            d_workstream << setfill('0') << setw(2) << etm->tm_hour << ':' <<
            setfill('0') << setw(2) << etm->tm_min << ':' <<
            setfill('0') << setw(2) << etm->tm_sec << ' ';


            switch(level)
            {
            case Errors:
                d_workstream << "(Error)\t";
                break;

            case Warnings:
                d_workstream << "(Warn)\t";
                break;

            case Standard:
                d_workstream << "(Std) \t";
                break;

            case Informative:
                d_workstream << "(Info) \t";
                break;

            case Insane:
                d_workstream << "(Insan)\t";
                break;

            default:
                d_workstream << "(Unkwn)\t";
                break;
            }

            d_workstream << message << endl;

            if (d_caching)
            {
                d_cache.push_back(std::make_pair(d_workstream.str(), level));
            }
            else if (d_level >= level)
            {

                d_ostream << d_workstream.str();

                d_ostream.flush();
            }
        }
    }
