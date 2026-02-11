gen_load_ppi_llprefixlen()
{
    struct slist *s1, *s2;


    if (reg_off_ll != -1)
    {


        s1 = new_stmt(BPF_LD | BPF_B | BPF_ABS);
        s1->s.k = 3;
        s2 = new_stmt(BPF_ALU | BPF_LSH | BPF_K);
        sappend(s1, s2);
        s2->s.k = 8;
        s2 = new_stmt(BPF_MISC | BPF_TAX);
        sappend(s1, s2);


        s2 = new_stmt(BPF_LD | BPF_B | BPF_ABS);
        sappend(s1, s2);
        s2->s.k = 2;
        s2 = new_stmt(BPF_ALU | BPF_OR | BPF_X);
        sappend(s1, s2);


        s2 = new_stmt(BPF_ST);
        s2->s.k = reg_off_ll;
        sappend(s1, s2);


        s2 = new_stmt(BPF_MISC | BPF_TAX);
        sappend(s1, s2);

        return (s1);
    }
    else
        return (NULL);
}
