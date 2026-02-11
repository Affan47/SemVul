calRelativePosition(int head, int i, char type) {
    int max = type == 'w' ? maxLeft(head) : maxTop(head);

    return FbTk::RelCalcHelper::calPercentageOf((i - max), getGap(head, type));
}
