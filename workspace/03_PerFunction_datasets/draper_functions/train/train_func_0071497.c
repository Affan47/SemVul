cacheAbbreviationsExpansions()
{
    cache.clear();

    std::ifstream abbr_file(abbreviations.c_str());
    if (!abbr_file) {
        logger << ERROR << "Could not open abbreviations file: " << abbreviations << endl;


    } else {
        logger << INFO << "Caching abbreviations/expansions from file: " << abbreviations << endl;

        std::string buffer;
        std::string abbreviation;
        std::string expansion;
        std::string::size_type tab_pos;
        while (getline(abbr_file, buffer)) {
            tab_pos = buffer.find_first_of('\t');
            if (tab_pos == std::string::npos) {
                logger << ERROR << "Error reading abbreviations/expansions from file: " << abbreviations << endl;
            } else {
                abbreviation = buffer.substr(0, tab_pos);
                expansion    = buffer.substr(tab_pos + 1, std::string::npos);

                logger << INFO << "Caching abbreviation: " << abbreviation << " - expansion: " << expansion << endl;
                cache[abbreviation] = expansion;
            }
        }

        abbr_file.close();
    }
}
