traverse_back(commit_list *cl, int max)
{
        struct commit_node*ln;
        int i, inc;

        ln = *cl;
        if (max < 0) {
                i = max - 1;
                inc = 0;
        } else {
                i = 0;
                inc = 1;
        }
        for (; *cl && i < max; i += inc) {
                ln = *cl;
                *cl = (*cl)->prev;
        }
        if (!*cl) {
                *cl = ln;
                i--;
        }

        return i;
}
