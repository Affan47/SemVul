printfFormatType(std::ostream& os, const std::string& specifier, bool isUnsigned)
{
    os << "\'";
    if (specifier[0] == 'l') {
        if (specifier[1] == 'l')
            os << (isUnsigned ? "unsigned " : "") << "long long";
        else
            os << (isUnsigned ? "unsigned " : "") << "long";
    } else if (specifier.find("I32") != std::string::npos) {
        os << (isUnsigned ? "unsigned " : "") << "__int32";
    } else if (specifier.find("I64") != std::string::npos) {
        os << (isUnsigned ? "unsigned " : "") << "__int64";
    } else if (specifier[0] == 'I') {
        os << (isUnsigned ? "size_t" : "ptrdiff_t");
    } else if (specifier[0] == 'j') {
        if (isUnsigned)
            os << "uintmax_t";
        else
            os << "intmax_t";
    } else if (specifier[0] == 'z') {
        if (specifier[1] == 'd')
            os << "ssize_t";
        else
            os << "size_t";
    } else if (specifier[0] == 't') {
        os << (isUnsigned ? "unsigned " : "") << "ptrdiff_t";
    } else if (specifier[0] == 'L') {
        os << (isUnsigned ? "unsigned " : "") << "long long";
    } else {
        os << (isUnsigned ? "unsigned " : "") << "int";
    }
    os << "\'";
}
