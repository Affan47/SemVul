length(input_ty *this)
{
        struct stat     st;

        if (fstat(fileno(stdin), &st) < 0)
                return -1;
        if (!S_ISREG(st.st_mode))
                return -1;
        return st.st_size;
}
