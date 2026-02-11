IsState(hsState *Buf, hsState State, size_t Len) {

    for (;Len > 0; Buf++, --Len)
        if (*Buf != State)
            return 0;

    return 1;
}
