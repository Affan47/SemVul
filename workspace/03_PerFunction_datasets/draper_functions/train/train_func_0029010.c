compile(const String &str, const String &source, const String &group)
    {
        ScriptLexer lexer;
        ScriptParser parser;
        ConcreteNodeListPtr nodes = parser.parse(lexer.tokenize(str, source));
        return compile(nodes, group);
    }
