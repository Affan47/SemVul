erl_length_x(const ETERM *ep) {
    int n = 0;

    if (!ep) return -1;

    while (ERL_TYPE(ep) == ERL_LIST) {
       n++;
       ep = TAIL(ep);
    }

    return n;
}
