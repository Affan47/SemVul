getnumchildren(const Token *tok, std::list<MathLib::bigint> &numchildren)
{
    if (tok->astOperand1() && tok->astOperand1()->isNumber())
        numchildren.push_back(MathLib::toLongNumber(tok->astOperand1()->str()));
    else if (tok->astOperand1() && tok->str() == tok->astOperand1()->str())
        getnumchildren(tok->astOperand1(), numchildren);
    if (tok->astOperand2() && tok->astOperand2()->isNumber())
        numchildren.push_back(MathLib::toLongNumber(tok->astOperand2()->str()));
    else if (tok->astOperand2() && tok->str() == tok->astOperand2()->str())
        getnumchildren(tok->astOperand2(), numchildren);
}
