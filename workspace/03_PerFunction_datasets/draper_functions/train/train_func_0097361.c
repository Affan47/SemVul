evalCondition (string cond, Scope *scope, int level, StackFrame *stack, StaticLink *staticLink) {
#if defined(_CC_GCC) && __GNUC__ == 2
    std::strstream stream ;
#else
    std::stringstream stream ;
#endif
    stream << cond ;
    Context ctx (stream, aikido->currentContext) ;
    aikido->currentContext = &ctx ;
    aikido->readLine() ;
    aikido->nextToken() ;
    int errors = aikido->numErrors ;
    noaccesscheck = true ;
    stopped = false ;
    bool result = false ;
    try {
        Value v = aikido->getExpression (stack, staticLink, scope, level) ;
        noaccesscheck = false ;
        stopped = true ;
        if (aikido->numErrors == errors) {
            result = v ;
        }
    } catch (...) {
        noaccesscheck = false ;
        stopped = true ;
    }
    aikido->currentContext = ctx.getPrevious() ;
    return result ;
}
