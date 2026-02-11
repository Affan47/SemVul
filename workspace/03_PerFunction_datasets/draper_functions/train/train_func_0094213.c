unary(Literal p, Literal x) const { return s->isTrue(x) || s->force(x, Antecedent(p)); }
