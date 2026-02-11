Append(ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return l->append(r);
        return l ? l : r;
    }
