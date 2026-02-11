siftup(Heap *h, int k)
{
    for (;;) {
        int l, r, s;

        l = k*2 + 1;
        r = k*2 + 2;


        s = k;
        if (l < h->len && less(h, l, s)) s = l;
        if (r < h->len && less(h, r, s)) s = r;

        if (s == k) {
            return;
        }

        swap(h, k, s);
        k = s;
    }
}
