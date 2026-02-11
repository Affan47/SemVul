print0x0007(std::ostream& os, const Value& value, const ExifData*)
    {
        if (value.count() == 3) {
            for (int i = 0; i < 3; ++i) {
                if (value.toRational(i).second == 0) {
                    return os << "(" << value << ")";
                }
            }
            std::ostringstream oss;
            oss.copyfmt(os);
            const float sec = 3600 * value.toFloat(0)
                              + 60 * value.toFloat(1)
                              + value.toFloat(2);
            int p = 0;
            if (sec != static_cast<int>(sec)) p = 1;

            const int hh = static_cast<int>(sec / 3600);
            const int mm = static_cast<int>((sec - 3600 * hh) / 60);
            const float ss = sec - 3600 * hh - 60 * mm;

            os << std::setw(2) << std::setfill('0') << std::right << hh << ":"
               << std::setw(2) << std::setfill('0') << std::right << mm << ":"
               << std::setw(2 + p * 2) << std::setfill('0') << std::right
               << std::fixed << std::setprecision(p) << ss;

            os.copyfmt(oss);
        }
        else {
            os << value;
        }

        return os;
    }
