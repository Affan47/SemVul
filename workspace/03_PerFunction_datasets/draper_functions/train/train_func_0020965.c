init_pointer(std::list<ExecutionPath *> &checks, const Token *tok) {
        const unsigned int varid(tok->varId());
        if (!varid)
            return;


        std::list<ExecutionPath *>::iterator it = checks.begin();
        while (it != checks.end()) {
            UninitVar *c = dynamic_cast<UninitVar *>(*it);
            if (c && c->varId == varid) {
                if (c->alloc || c->var->isArray()) {
                    delete c;
                    checks.erase(it++);
                    continue;
                } else {
                    use_pointer(checks, tok);
                }
            }

            ++it;
        }
    }
