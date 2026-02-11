parse(const Token &tok, std::list<ExecutionPath *> &checks) const {
        if (Token::Match(tok.previous(), "[;{}]")) {

            if (Token::Match(&tok, "%type% %var% ;") ) {
                checks.push_back(new ExecutionPathBufferOverrun(owner, arrayInfo, tok.next()->varId()));
                return tok.tokAt(2);
            }


            if (Token::Match(&tok, "%var% = %num% ;")) {
                assign_value(checks, tok.varId(), tok.strAt(2));
                return tok.tokAt(3);
            }
        }


        if (Token::Match(&tok, "%var% =")) {
            assign_value(checks, tok.varId(), "0");
            return &tok;
        }


        if (Token::Match(tok.tokAt(-2), "(|, & %var% ,|)")) {
            assign_value(checks, tok.varId(), "0");
            return &tok;
        }


        if (Token::Match(&tok, "%var% [ %var% ]")) {
            array_index(&tok, checks, tok.varId(), tok.tokAt(2)->varId());
            return tok.tokAt(3);
        }

        return &tok;
    }
