calcWidth(const char *s, int count) {
    if (!prettyClock)
        return clockFont->textWidth(s, count);
    else {
        int len = 0;

        while (count--) {
            ref<YPixmap> p = getPixmap(*s++);
            if (p != null)
                len += p->width();
        }
        return len;
    }
}
