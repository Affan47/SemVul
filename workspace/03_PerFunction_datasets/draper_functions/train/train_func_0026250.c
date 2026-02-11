translatePriority(int type)
{
    typedef struct
    {
        int type;
        int priority;
    } PrioritiesRec;


    PrioritiesRec priorities[] = {{ L_ERROR, LOG_ERR },
                                  { L_WARN, LOG_WARNING },
                                  { L_INFO, LOG_NOTICE },
                                  { L_FORBIDDEN, LOG_DEBUG },
                                  { L_UNCACHEABLE, LOG_DEBUG },
                                  { L_SUPERSEDED, LOG_DEBUG },
                                  { L_VARY, LOG_DEBUG },
                                  { 0, 0 }};
    PrioritiesRec *current;

    current = priorities;
    while(current->type) {
        if(current->type == type) {
            return current->priority;
        }
        current++;
    }

    return LOG_DEBUG;
}
