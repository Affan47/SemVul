parseLoopBody(const Token *tok, std::list<ExecutionPath *> &checks) const {
        while (tok) {
            if (Token::Match(tok, "{|}|return|goto|break|if"))
                return;
            const Token *next = parse(*tok, checks);
            if (next)
                tok = tok->next();
        }
    }

}
