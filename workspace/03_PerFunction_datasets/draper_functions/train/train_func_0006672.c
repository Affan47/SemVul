fa_dot(FILE *out, struct fa *fa) {
    fprintf(out, "digraph {\n  rankdir=LR;");
    list_for_each(s, fa->initial) {
        if (s->accept) {
            fprintf(out, "\"%p\" [shape=doublecircle];\n", s);
        } else {
            fprintf(out, "\"%p\" [shape=circle];\n", s);
        }
    }
    fprintf(out, "%s -> \"%p\";\n", fa->deterministic ? "dfa" : "nfa",
            fa->initial);

    struct re_str str;
    MEMZERO(&str, 1);
    list_for_each(s, fa->initial) {
        for_each_trans(t, s) {
            fprintf(out, "\"%p\" -> \"%p\" [ label = \"", s, t->to);
            if (fa->trans_re) {
                re_as_string(t->re, &str);
                for (int i=0; i < str.len; i++) {
                    print_char(out, str.rx[i]);
                }
                release_re_str(&str);
            } else {
                print_char(out, t->min);
                if (t->min != t->max) {
                    fputc('-', out);
                    print_char(out, t->max);
                }
            }
            fprintf(out, "\" ];\n");
        }
    }
    fprintf(out, "}\n");
}
