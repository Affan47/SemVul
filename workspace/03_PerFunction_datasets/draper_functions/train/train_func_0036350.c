pushLabel(const Identifier& label)
{
    if (!seenLabels.add(label).second)
        return false;

    seenLabelsStack.append(label);
    pendingLabels.append(label);

    return true;
}
