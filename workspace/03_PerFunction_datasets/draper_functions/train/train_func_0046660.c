pop(stableStack** top) {
    if(*top == NULL) return NULL;
    stableStack* rval = *top;
    *top = (*top)->prev;

    return rval;
    }
