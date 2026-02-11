print_debug_sa(Shrink_args *sa)
{
    int i;

    mfprintf(stdout, "\n<<< shrink_args : %s >>>\n", sa->callee_module->name);
    mfprintf(stdout, "arg_num : %d\n", sa->arg_num);
    mfprintf(stdout, "max_set : %d\n", sa->max_set);

    if (sa->max_set != 0)
        mfprintf(stdout, "[under mean : nth_arg_is_same_operand]\n");

    for (i = 0; i < sa->max_set; i++) {
        mfprintf(stdout, "IntSet[%d] : ", i);
        see_IntSet(sa->arg_set[i]);
    }
}
