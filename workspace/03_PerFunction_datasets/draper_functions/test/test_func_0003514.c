operator<(const MoveData& m1, const MoveData& m2)
{
    return m1.count < m2.count || (m1.count == m2.count && m1.move < m2.move);
}
