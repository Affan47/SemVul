setDebugErrorFunction(PopplerDebugFunc function, const QVariant &closure)
    {
        Debug::debugFunction = function ? function : Debug::qDebugDebugFunction;
        Debug::debugClosure = closure;
    }
