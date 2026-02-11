processDihedral(SymmList& syms, double order, double x, double y,
                    bool dihedral, double angle, const yy::location& where)
    {
        if (order < 1.0)
            CfdgError::Error(where, "Rotational symmetry order must be one or larger");
        agg::trans_affine reg;
        agg::trans_affine_reflection mirror(angle);
        reg.translate(-x, -y);
        int num = (int)order;
        order = 2.0 * M_PI / order;
        for (int i = 0; i < num; ++i) {
            agg::trans_affine tr(reg);
            if (i) tr.rotate(i * order);
            agg::trans_affine tr2(tr);
            tr2 *= mirror;
            tr.translate(x, y);
            tr2.translate(x, y);
            addUnique(syms, tr);
            if (dihedral) addUnique(syms, tr2);
        }
    }
