print0x0007(std::ostream& os,
                                               const Value& value,
                                               const ExifData*)
    {
        std::string focus = value.toString();
        if      (focus == "AF-C  ") os << _("Continuous autofocus");
        else if (focus == "AF-S  ") os << _("Single autofocus");
        else if (focus == "AF-A  ") os << _("Automatic");
        else                      os << "(" << value << ")";
        return os;
    }
