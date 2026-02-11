for_maxvalue(const Token * const stepvalue, const std::string &min_value, std::string &max_value)
{
    if (!MathLib::isInt(stepvalue->str()))
        return false;


    const MathLib::bigint num = MathLib::toLongNumber(stepvalue->str());
    MathLib::bigint max = MathLib::toLongNumber(max_value);
    const MathLib::bigint min = MathLib::toLongNumber(min_value);
    max = ((max - min) / num) * num + min;
    max_value = MathLib::toString<MathLib::bigint>(max);
    return true;
}
