update_secondary_correlations(int node1, int node2,
        float outer)
{

    if ((node1 == to && node2 == from) || (node1 == from && node2 == to))
        return;

    node1 = (node1 == to ? from : (node1 == from) ? to : node1);
    node2 = (node2 == to ? from : (node2 == from) ? to : node2);

    float scale = outer * SECOND_DEGREE / MAX_CORRELATION;
    update_correlation(node1, node2, weight * scale);

    return;
}
