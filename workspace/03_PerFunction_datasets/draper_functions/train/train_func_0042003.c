print0x0085(std::ostream& os,
                                               const Value& value,
                                               const ExifData*)
    {
        Rational distance = value.toRational();
        if (distance.first == 0) {
            os << _("Unknown");
        }
        else if (distance.second != 0) {
            std::ostringstream oss;
            oss.copyfmt(os);
            os << std::fixed << std::setprecision(2)
               << (float)distance.first / distance.second
               << " m";
            os.copyfmt(oss);
        }
        else {
            os << "(" << value << ")";
        }
        return os;
    }
