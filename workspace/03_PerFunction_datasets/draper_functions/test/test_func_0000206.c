print0x000f(std::ostream& os,
                                                  const Value& value,
                                                  const ExifData*)
    {
        if (value.count() < 2 || value.typeId() != unsignedByte) {
            return os << value;
        }
        long l0 = value.toLong(0);
        long l1 = value.toLong(1);
        if      (l0 ==  0 && l1 ==  1) os << _("Spot mode on");
        else if (l0 ==  0 && l1 == 16) os << _("Spot mode off or 3-area (high speed)");
        else if (l0 ==  1 && l1 ==  0) os << _("Spot focussing");
        else if (l0 ==  1 && l1 ==  1) os << _("5-area");
        else if (l0 == 16 && l1 ==  0) os << _("1-area");
        else if (l0 == 16 && l1 == 16) os << _("1-area (high speed)");
        else if (l0 == 32 && l1 ==  0) os << _("3-area (auto)");
        else if (l0 == 32 && l1 ==  1) os << _("3-area (left)");
        else if (l0 == 32 && l1 ==  2) os << _("3-area (center)");
        else if (l0 == 32 && l1 ==  3) os << _("3-area (right)");
        else os << value;
        return os;
    }
