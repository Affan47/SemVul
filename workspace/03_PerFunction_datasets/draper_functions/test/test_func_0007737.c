print0x0209(std::ostream& os, const Value& value, const ExifData*)
    {
        if (value.typeId() != asciiString && value.typeId() != undefined) {
            return os << value;
        }

        char ch;
        int size = value.size();
        for (int i = 0; i < size && ((ch = (char)value.toLong(i)) != '\0'); i++) {
            os << ch;
        }
        return os;
    }
