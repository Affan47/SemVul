setLogFilename(const String& filename, bool append)
    {

        if (d_ostream.is_open())
        {
            d_ostream.close();
        }

        d_ostream.open(filename.c_str(), std::ios_base::out | (append ? std::ios_base::app : std::ios_base::trunc));

        if (!d_ostream)
        {
            CEGUI_THROW("Logger::setLogFilename - Failed to open file.");
        }


        d_ostream.width(2);


        if (d_caching)
        {
            d_caching = false;

            std::vector<std::pair<String, LoggingLevel> >::iterator iter = d_cache.begin();

            while (iter != d_cache.end())
            {
                if (d_level >= (*iter).second)
                {

                    d_ostream << (*iter).first;

                    d_ostream.flush();
                }

                ++iter;
            }

            d_cache.clear();
        }
    }

}
