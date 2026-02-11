parse_noreturn()
{
    if (noreturn.empty()) {
        noreturn.insert("exit");
        noreturn.insert("_exit");
        noreturn.insert("_Exit");
        noreturn.insert("abort");
        noreturn.insert("err");
        noreturn.insert("verr");
        noreturn.insert("errx");
        noreturn.insert("verrx");
        noreturn.insert("ExitProcess");
        noreturn.insert("ExitThread");
        noreturn.insert("pthread_exit");
    }


    const std::size_t functionsCount = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functionsCount; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];


        bool isNoreturn = false;
        for (const Token *tok2 = scope->classStart->next(); tok2 != scope->classEnd; tok2 = tok2->next()) {
            if (Token::Match(tok2->previous(), "[;{}] exit (")) {
                isNoreturn = true;
                break;
            }
        }


        if (isNoreturn)
            noreturn.insert(scope->className);
        else
            notnoreturn.insert(scope->className);
    }
}
