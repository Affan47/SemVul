wordRabinKarpConstant(ajuint m)
{
    ajulong rm;
    ajuint i;

    rm = 1;

    for(i = 1; i <= m-1; i++)
        rm = (RK_RADIX * rm) % RK_MODULUS;

    return rm;
}
