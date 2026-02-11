breakString (Font *font,
                  const std::string &str,
                  const std::string &breakChars,
                  int targetWidth)
{
    if (font->get_width (str.c_str()) <= targetWidth)
        return str.size();

    bool breakFound = false;
    std::string::size_type pos = 0;
    while (true) {
        std::string::size_type nextpos = str.find_first_of (breakChars, pos);

        if (nextpos == std::string::npos)

            return breakFound ? pos : str.size();

        if (font->get_width (str.substr(0, nextpos+1).c_str()) > targetWidth)

            return breakFound ? pos : nextpos + 1;

        pos = nextpos+1;
        breakFound = true;
    }
}
