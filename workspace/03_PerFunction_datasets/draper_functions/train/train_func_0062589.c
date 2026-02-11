sharesEdge(const Triangle& t) const
        {
            return( (a == t.a && b == t.c) ||
                    (a == t.b && b == t.a) ||
                    (a == t.c && b == t.b) ||
                    (b == t.a && c == t.c) ||
                    (b == t.b && c == t.a) ||
                    (b == t.c && c == t.b) ||
                    (c == t.a && a == t.c) ||
                    (c == t.b && a == t.a) ||
                    (c == t.c && a == t.b) );
        }
