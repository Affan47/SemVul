parseend()
{
    boolean done = FALSE;
    while (!done) {
        linex += scan1(&line[linex]);
        switch (token[0]) {
        case ',':
            ndurp = TRUE;
            ntime = 0L;
            done = TRUE;
            break;
        case ';':
        case '\n':
        case EOS:
            done = TRUE;
            break;
        case ' ':
        case '\t':
            break;
        default:
            fferror("Unexpected token");
            linex += scan();
            break;
        }
    }
}
