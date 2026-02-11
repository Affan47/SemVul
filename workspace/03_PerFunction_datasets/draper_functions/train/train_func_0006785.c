CheckBlock() {
    if (BB.Row == -1 && BE.Row == 1) {
        BB.Col = -1;
        BE.Col = -1;
        return 0;
    }
    if (BB.Row == -1 || BE.Row == -1) return 0;
    if (BB.Row >= RCount) BB.Row = RCount - 1;
    if (BE.Row >= RCount) BE.Row = RCount - 1;
    switch(BlockMode) {
    case bmLine:
        BB.Col = 0;
        BE.Col = 0;
        if (BB.Row >= BE.Row) return 0;
        break;
    case bmColumn:
        if (BB.Col >= BE.Col) return 0;
        if (BB.Row >= BE.Row) return 0;
        break;
    case bmStream:
        if (BB.Row > BE.Row) return 0;
        if (BB.Row == BE.Row && BB.Col >= BE.Col) return 0;
        break;
    }
    return 1;
}
