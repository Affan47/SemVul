mergeOut(Block *b) {
    findMinOutConstraint();
    b->findMinOutConstraint();
    while (!b->out->empty())
    {
        out->push(b->out->top());
        b->out->pop();
    }
}
