print(char ch)
        {


            if (ch == '"')
                in_string = !in_string;

            if (!in_string && std::isspace(static_cast<unsigned char>(ch)))
            {

                if (!std::isspace(static_cast<unsigned char>(prev)))
                {
                    if (column >= linewidth)
                    {
                        break_line();
                        if (column == 0 && ch == ' ')
                        {
                            ++column;
                            out += ' ';
                        }
                    }
                    else
                    {
                        ++column;
                        out += ' ';
                    }
                }
            }
            else
            {


                if (!in_string
                    && column >= linewidth
                    && (ch == '<' && std::isspace(static_cast<unsigned char>(prev))))
                    break_line();
                out += ch;
                ++column;
            }

            prev = ch;
        }
