checkIntRelation(const std::string &op, const MathLib::bigint value1, const MathLib::bigint value2)
{
    return (op == "==" && value1 == value2) ||
           (op == "!=" && value1 != value2) ||
           (op == ">"  && value1 >  value2) ||
           (op == ">=" && value1 >= value2) ||
           (op == "<"  && value1 <  value2) ||
           (op == "<=" && value1 <= value2);
}
