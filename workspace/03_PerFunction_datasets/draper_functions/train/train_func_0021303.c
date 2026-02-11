PQMUL_R2 (qword *U, qword *Y, qword *result)
{
    qword stack;
    qword part1;
    qword part2;
    qword part3;

    EMULQ(U->d_high, Y->d_high, &stack);


    PQLSH_R0(&stack, &part1);

    EMULQ(U->d_high, Y->d_low, &stack);

    EMULQ(U->d_low, Y->d_high, &part2);

    PQADD_R0(&stack, &part2, &part3);

    PQADD_R0(&part1, &part3, &stack);


    PQLSH_R0(&stack, &part1);

    EMULQ(U->d_low, Y->d_low, &stack);


    PQADD_R0(&part1, &stack, result);
}
