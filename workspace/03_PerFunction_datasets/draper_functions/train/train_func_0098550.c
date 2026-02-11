getTemplateDeclarations(Token *tokens, bool &codeWithTemplates)
{
    std::list<Token *> templates;
    for (Token *tok = tokens; tok; tok = tok->next()) {

        if (Token::Match(tok, "namespace %type% {"))
            tok = tok->linkAt(2);

        if (Token::simpleMatch(tok, "template <")) {
            Token *parmEnd = tok->next()->findClosingBracket();
            codeWithTemplates = true;

            int indentlevel = 0;
            for (const Token *tok2 = parmEnd; tok2; tok2 = tok2->next()) {
                if (tok2->str() == "(")
                    ++indentlevel;
                else if (tok2->str() == ")")
                    --indentlevel;

                if (indentlevel)
                    continue;


                if (tok2->str() == ";")
                    break;

                if (tok2->str() == "{") {
                    templates.push_back(tok);
                    break;
                }
            }
        }
    }
    return templates;
}
