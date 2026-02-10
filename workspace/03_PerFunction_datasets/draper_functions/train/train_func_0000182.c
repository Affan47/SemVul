format_one(std::ostream& os, const option_description& opt,
                        unsigned first_column_width, unsigned line_length)
        {
            stringstream ss;
            ss << "  " << opt.format_name() << ' ' << opt.format_parameter();


            os << ss.str();

            if (!opt.description().empty())
            {
                if (ss.str().size() >= first_column_width)
                {
                   os.put('\n');
                   for (unsigned pad = first_column_width; pad > 0; --pad)
                   {
                      os.put(' ');
                   }
                } else {
                   for(unsigned pad = first_column_width - static_cast<unsigned>(ss.str().size()); pad > 0; --pad)
                   {
                      os.put(' ');
                   }
                }

                format_description(os, opt.description(),
                                   first_column_width, line_length);
            }
        }
