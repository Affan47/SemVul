popLabel()
{
    Identifier name = seenLabelsStack.last();

    seenLabelsStack.removeLast();
    seenLabels.remove  (name);
    labelTargets.remove(name);
    ASSERT(pendingLabels.isEmpty());
}
