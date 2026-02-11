constval(const Token * tok)
{
    return tok && tok->values.size() == 1U && tok->values.front().varId == 0U;
}
