checkExpressionRange(const std::list<const Function*> &constFunctions,
                                      const Token *start,
                                      const Token *end,
                                      const std::string &toCheck)
{
    if (!start || !end)
        return;
    Expressions expressions(_tokenizer->getSymbolDatabase(), constFunctions);
    std::string opName;
    int level = 0;
    for (const Token *tok = start->next(); tok && tok != end; tok = tok->next()) {
        if (tok->str() == ")")
            level--;
        else if (tok->str() == "(")
            level++;

        if (level == 0 && Token::Match(tok, toCheck.c_str())) {
            opName = tok->str();
            expressions.endExpr(tok);
        } else {
            expressions.append(tok);
        }
    }
    expressions.endExpr(end);
    std::map<std::string,ExpressionTokens>::const_iterator it = expressions.getMap().begin();
    for (; it != expressions.getMap().end(); ++it) {

        bool valid = true;
        unsigned int parenthesis = 0;
        unsigned int brackets = 0;


        if (Token::Match(it->second.end->previous(), "%op% &")) {
            continue;
        }

        for (const Token *tok = it->second.start; tok && tok != it->second.end; tok = tok->next()) {
            if (tok->str() == "(") {
                ++parenthesis;
            } else if (tok->str() == ")") {
                if (parenthesis == 0) {
                    valid = false;
                    break;
                }
                --parenthesis;
            } else if (tok->str() == "[") {
                ++brackets;
            } else if (tok->str() == "]") {
                if (brackets == 0) {
                    valid = false;
                    break;
                }
                --brackets;
            } else if (tok->type() == Token::eIncDecOp) {
                valid = false;
                break;
            }
        }

        if (!valid || parenthesis!=0 || brackets!=0)
            continue;

        const ExpressionTokens &expr = it->second;
        if (expr.count > 1 && !expr.inconclusiveFunction) {
            duplicateExpressionError(expr.start, expr.start, opName);
        }
    }
}
