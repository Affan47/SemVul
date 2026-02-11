main(int argc, char **argv)
{
    MatrixD gauss = Kernel::gaussian(7, 0.84 * 0.84);

    print(gauss);

    return 0;
}
