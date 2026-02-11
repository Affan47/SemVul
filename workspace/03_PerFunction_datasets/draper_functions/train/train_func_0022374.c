nextEnumerated() {
        h2x_assert(is_enumerated);
        if (brother) {
            ParagraphTree *next = brother->firstEnumerated();
            if (next && next->enumeration == (enumeration+1)) {
                return next;
            }
        }
        return 0;
    }
