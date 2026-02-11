check_symmetric_hkl(const SgOps &sg_ops, const Miller &p1,
                                              const Miller &p2)
{
    for (size_t i = 0; i < sg_ops.seitz.size(); ++i)
    {
        const int* R = sg_ops.seitz[i].R;
        int h = R[0] * p1.h + R[3] * p1.k + R[6] * p1.l;
        int k = R[1] * p1.h + R[4] * p1.k + R[7] * p1.l;
        int l = R[2] * p1.h + R[5] * p1.k + R[8] * p1.l;
        if (h == p2.h && k == p2.k && l == p2.l)
            return  true;

        if (h == -p2.h && k == -p2.k && l == -p2.l)
            return true;
    }
    return false;
}
