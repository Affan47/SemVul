KL_Divergence(const Gaussian &g1, const Gaussian &g2)
{
    float total = 0;
    for (int i = 0; i < Gaussian::NumDimensions; ++i)
    {

        const float MinVariance = 10.0f;
        float var1 = std::max(g1.vars[i], MinVariance);
        float var2 = std::max(g2.vars[i], MinVariance);
        float dist = var1 / var2 + var2 / var1 +
            pow(g1.means[i] - g2.means[i], 2.0f) *
            (1.0f / var1 + 1.0f / var2);

        total += dist - 2;
    }
    return total;
}
