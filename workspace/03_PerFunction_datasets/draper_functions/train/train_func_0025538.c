operator<<(std::ostream& o, GradientFill::SpreadMode t)
{
    switch (t) {
        case GradientFill::PAD:
            return o << "pad";
        case GradientFill::REPEAT:
            return o << "repeat";
        default:
        case GradientFill::REFLECT:
            return o << "reflect";
    }
}
