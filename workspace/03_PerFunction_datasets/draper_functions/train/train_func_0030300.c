printInt(std::ostream& out, int64_t v, const std::string& name)
    {
        if (v >= 0)
        {
            printUInt(out, v, name);
        }
        else if (v >= std::numeric_limits<int8_t>::min() && v <= std::numeric_limits<int8_t>::max())
        {
            out << static_cast<char>(name.empty() ? Serializer::TypePlainInt8 : Serializer::TypeInt8);
            if (!name.empty())
                out << name << '\0';
            out << static_cast<char>(v);
        }
        else if (v >= std::numeric_limits<int16_t>::min() && v <= std::numeric_limits<int16_t>::max())
        {
            out << static_cast<char>(name.empty() ? Serializer::TypePlainInt16 : Serializer::TypeInt16);
            if (!name.empty())
                out << name << '\0';
            out << static_cast<char>(v >> 8)
                << static_cast<char>(v);
        }
        else if (v >= std::numeric_limits<int32_t>::min() && v <= std::numeric_limits<int32_t>::max())
        {
            out << static_cast<char>(name.empty() ? Serializer::TypePlainInt32 : Serializer::TypeInt32);
            if (!name.empty())
                out << name << '\0';
            out << static_cast<char>(v >> 24)
                << static_cast<char>(v >> 16)
                << static_cast<char>(v >> 8)
                << static_cast<char>(v);
        }
        else
        {
            out << static_cast<char>(name.empty() ? Serializer::TypePlainInt64 : Serializer::TypeInt64);
            if (!name.empty())
                out << name << '\0';
            out << static_cast<char>(v >> 56)
                << static_cast<char>(v >> 48)
                << static_cast<char>(v >> 40)
                << static_cast<char>(v >> 32)
                << static_cast<char>(v >> 24)
                << static_cast<char>(v >> 16)
                << static_cast<char>(v >> 8)
                << static_cast<char>(v);
        }
    }
