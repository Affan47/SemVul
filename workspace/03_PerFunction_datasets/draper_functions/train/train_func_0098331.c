printXmpDate(std::ostream& os, const Value& value, const ExifData*)
    {
        if (!(value.size() == 19 || value.size() == 20) || value.typeId() != xmpText) {
            return os << value;
        }

        std::string stringValue = value.toString();
        if (stringValue[19] == 'Z') {
            stringValue = stringValue.substr(0, 19);
        }
        for (unsigned int i = 0; i < stringValue.length(); ++i) {
            if (stringValue[i] == 'T') stringValue[i] = ' ';
            if (stringValue[i] == '-') stringValue[i] = ':';
        }

        return os << stringValue;
    }
