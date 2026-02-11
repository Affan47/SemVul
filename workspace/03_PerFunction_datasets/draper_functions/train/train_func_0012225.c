operator<(const RLEData& b) const
{
    uchar ac, bc;
    for (int i = 0; i < qMin(size(), b.size()); i++) {
        ac = at(i);
        bc = b[i];
        if (ac != bc)
            return ac < bc;
    }
    return size() < b.size();
}
