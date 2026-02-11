quietUnwind(int depth)
{
    ASSERT(m_exceptionHandlers.size() >= size_t(depth));
    for (int e = 0; e < depth; ++e) {
        HandlerType type = m_exceptionHandlers.last().type;
        m_exceptionHandlers.removeLast();

        switch (type) {
        case JumpToCatch:
            break;
        case PopScope:
            popScope();
            break;
        case RemoveDeferred:
            m_deferredCompletions.removeLast();
            break;
        case Silent:
            ASSERT(0);
            break;
        }
    }
}
