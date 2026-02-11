normalize()
    {
        if(z.iszero() || z.isone()) return;
        gfield tmp;
        z.invert();
        tmp.square(z);
        x.mul(tmp);
        y.mul(tmp).mul(z);
        z = bigint<1>(1);
    }
