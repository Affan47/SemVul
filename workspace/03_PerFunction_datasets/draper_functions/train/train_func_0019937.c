conditionIsTrue(const Token *condition, const std::map<unsigned int, MathLib::bigint> &programMemory)
{
    if (!condition)
        return false;
    if (condition->str() == "||") {
        const bool result1 = conditionIsTrue(condition->astOperand1(), programMemory);
        const bool result2 = result1 ? true : conditionIsTrue(condition->astOperand2(), programMemory);
        return result2;
    }
    std::map<unsigned int, MathLib::bigint> progmem(programMemory);
    bool error = false;
    MathLib::bigint result = 0;
    execute(condition, &progmem, &result, &error);
    return !error && result == 1;
}
