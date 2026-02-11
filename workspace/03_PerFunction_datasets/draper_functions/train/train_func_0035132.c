isTypeWithoutSideEffects(const Tokenizer *tokenizer, const Variable* var)
{
    return ((var && (!var->isClass() || var->isPointer() || Token::simpleMatch(var->typeStartToken(), "std ::"))) || !tokenizer->isCPP());
}
