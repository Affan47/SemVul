hiddenCount() const
{
    int rows = rowCount();
    int hidden = 0;

    for (int i=0; i<rows; ++i) {
        if (isHidden(index(i, 0))) {
            hidden++;
        }
    }

    return hidden;
}
