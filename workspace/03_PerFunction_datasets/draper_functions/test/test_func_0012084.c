removeObject(Node n) {
        Triples triples = m_s->match(Triple(n, Node(), Node()));
        foreach (Triple t, triples) {
            if (t.b.type == Node::URI) {
                removePropertyNodes(n, Uri(t.b.value));
            }
        }
        m_s->remove(Triple(Node(), Node(), n));
    }
