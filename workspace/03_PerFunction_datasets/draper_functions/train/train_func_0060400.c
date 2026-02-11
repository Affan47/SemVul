limit_iterations(guint iters)
{


    return MAX(MIN(iters, 10000000), 1000);
}
