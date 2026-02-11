printImageSize(std::ostream& os, const Value& value, const ExifData*)
    {
        if (value.count() == 2)
            os << value.toString(0) << " x " << value.toString(1);
        else
            os << "(" << value << ")";

        return os;
    }
