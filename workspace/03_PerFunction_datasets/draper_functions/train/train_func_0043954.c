childrenOf(Node node) {
        Nodes nn;
        Triples tt = m_s->match(Triple(Node(), m_parentProp, node));
        foreach (Triple t, tt) nn << t.a;
        return nn;
    }
