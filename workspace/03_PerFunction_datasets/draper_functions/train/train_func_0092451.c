print0x0023(std::ostream& os,
                                                  const Value& value,
                                                  const ExifData*)
    {
        std::ostringstream oss;
        oss.copyfmt(os);
        os << std::fixed << std::setprecision(1)
           << value.toLong() / 3 << _(" EV");
        os.copyfmt(oss);

        return os;

    }
