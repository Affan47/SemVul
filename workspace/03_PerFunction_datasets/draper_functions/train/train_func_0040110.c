wxblockdouble_sort_bottomleft_topright( wxBlockDouble **a, wxBlockDouble **b)
{
    register wxDouble y = ((*a)->m_y2 - (*b)->m_y2);

    if (y > 0) return -1;
    if (y == 0) return  int((*a)->m_x1 - (*b)->m_x1);
    return 1;
}
