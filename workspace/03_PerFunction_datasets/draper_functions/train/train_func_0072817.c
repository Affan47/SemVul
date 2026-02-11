print0x9202(std::ostream& os, const Value& value, const ExifData*)
    {
        if (   value.count() == 0
            || value.toRational().second == 0) {
            return os << "(" << value << ")";
        }
        std::ostringstream oss;
        oss.copyfmt(os);
        os << "F" << std::setprecision(2) << fnumber(value.toFloat());
        os.copyfmt(oss);
        return os;
    }
