removeTill(ParagraphTree *after) {
        ParagraphTree *removed    = this;
        ParagraphTree *after_pred = this;

        while (1) {
            h2x_assert(after_pred);
            h2x_assert(after_pred->brother);

            if (after_pred->brother == after) {
                after_pred->brother = 0;
                break;
            }
            after_pred = after_pred->brother;
        }

        return removed;
    }
