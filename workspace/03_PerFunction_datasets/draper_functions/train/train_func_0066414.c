instantiateMatch(const Token *instance, const std::string &name, std::size_t numberOfArguments, const char patternAfter[])
{
    if (!Token::simpleMatch(instance, (name + " <").c_str()))
        return false;

    if (numberOfArguments != TemplateSimplifier::templateParameters(instance->next()))
        return false;

    if (patternAfter) {
        const Token *tok = instance;
        unsigned int indentlevel = 0;
        for (tok = instance; tok && (tok->str() != ">" || indentlevel > 0) && (tok->str() != ">>" || indentlevel > 1); tok = tok->next()) {
            if (Token::Match(tok, "[<,] %var% <") && templateParameters(tok->tokAt(2)) > 0)
                ++indentlevel;
            if (indentlevel > 0 && tok->str() == ">")
                --indentlevel;
            if (indentlevel > 0 && tok->str() == ">>")
                indentlevel -= (indentlevel > 1) ? 2 : 1;
        }
        if (!tok || !Token::Match(tok->next(), patternAfter))
            return false;
    }


    return true;
}
