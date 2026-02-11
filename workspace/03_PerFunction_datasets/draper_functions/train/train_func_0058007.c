modularizeRow(TabRow & row, const bool * integerVar)
{
    const int& n = row.getNumElements();
    const int* ind = row.getIndices();
    for (int i = 0 ; i < n ; i++)
    {
        const int &ni = ind[i];
        if (integerVar[ni])
            row[ni] = modularizedCoef(row[ni],row.rhs);
    }
}
