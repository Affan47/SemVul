step6()
{
    double minimum = find_smallest();
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if (row_covered.at(row))
                grid_[row][column] += minimum;
            if (!column_covered.at(column))
                grid_[row][column] -= minimum;
        }
    }
    return 4;
}
