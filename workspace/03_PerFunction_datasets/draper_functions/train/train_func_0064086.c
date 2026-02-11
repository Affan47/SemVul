getItem(int no) {
    if (no < 0 || no >= getItemCount())
        return 0;
    updateItems();

    if (fItems) {
        return fItems[no];
    } else {
        YListItem *a = getFirst();
        for (int n = 0; a; a = a->getNext(), n++)
            if (n == no)
                return a;
    }
    return 0;
}
