addWindowListApp(YFrameWindow *frame) {
    if (!frame->client()->adopted())
        return 0;
    WindowListItem *item = new WindowListItem(frame);
    if (item) {
        insertApp(item);
    }
    return item;
}
