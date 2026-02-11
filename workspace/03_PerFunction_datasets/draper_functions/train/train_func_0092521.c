collect_generations(void)
{
    int i;
    Py_ssize_t n = 0;


    for (i = NUM_GENERATIONS-1; i >= 0; i--) {
        if (generations[i].count > generations[i].threshold) {


            if (i == NUM_GENERATIONS - 1
                && long_lived_pending < long_lived_total / 4)
                continue;
            n = collect_with_callback(i);
            break;
        }
    }
    return n;
}
