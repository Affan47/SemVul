clause_cmp (const void* x, const void* y) {
    return clause_size((clause*)x) > 2
           && (clause_size((clause*)y) == 2
               || clause_activity((clause*)x)
                  < clause_activity((clause*)y)) ? -1 : 1; }
