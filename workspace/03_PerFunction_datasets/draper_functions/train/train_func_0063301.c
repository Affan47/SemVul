tokAt(int index)
{
    Token *tok = this;
    int num = std::abs(index);
    while (num > 0 && tok) {
        if (index > 0)
            tok = tok->next();
        else
            tok = tok->previous();
        --num;
    }
    return tok;
}
