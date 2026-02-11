delegate (Value &s) {
    if (aikido->worker->isLoopback()) {
        if (parserDelegate == NULL) {
            runtimeError ("Unrecognized foreign command sequence");
        }
    }
    parserLock.acquire(true) ;
    Context ctx (ir->source, *s.stream, aikido->currentContext) ;
    aikido->currentContext = &ctx ;
    std::istream &currentStream = aikido->currentContext->getStream();
    int pass = aikido->currentPass ;
    parserLock.release(true) ;

    ctx.rewind() ;
    incRef (frame, stackframe) ;

    try {
        aikido->worker->parse(currentStream, frame, staticLink, scopeStack[scopeSP - 1], scopeStack[scopeSP - 1]->majorScope->level, ir->source, output.stream->getOutStream(), input.stream->getInStream(), &ctx, pass) ;
    } catch (...) {
        parserLock.acquire(true) ;
        aikido->currentContext = ctx.getPrevious() ;
        parserLock.release(true) ;
        throw ;
    }
    parserLock.acquire(true) ;
    aikido->currentContext = ctx.getPrevious() ;
    parserLock.release(true) ;
    decRef (frame, stackframe) ;
}
