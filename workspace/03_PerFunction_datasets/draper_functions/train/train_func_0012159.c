readSymbolToken() {
    Token t(read());

    if (t._type == Token::SYMBOL) {
        return t;
    }

    push(t);
    throw WrongTokenType(options.sourceFileName, t.line(), t.character(),
                         Token::SYMBOL, t._type);
}
