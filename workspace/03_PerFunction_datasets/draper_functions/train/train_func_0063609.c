main(int argc, const char * argv[])
{
    Runner runner;
    runner.run(&int_cmp, &make_unordered_array, &free_array);

    return 0;
}
