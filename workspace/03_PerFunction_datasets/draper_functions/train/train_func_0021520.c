compileAssignTernary(Token *&tok, AST_state& state)
{
    compileLogicOr(tok, state);
    while (tok) {


        if (tok->isAssignmentOp() || Token::Match(tok, "[?:]")) {
            if (tok->str() == "?" && tok->strAt(1) == ":") {
                state.op.push(0);
            }
            compileBinOp(tok, state, compileAssignTernary);
        } else break;
    }
}
