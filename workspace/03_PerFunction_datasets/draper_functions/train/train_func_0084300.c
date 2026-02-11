ToggleMark() {
    if (Count > 0) {
        if (IsMarked(Row)) {
            if (Unmark(Row) == 1) {
                NeedsRedraw = 1;
                return 1;
            }
        } else {
            if (Mark(Row) == 1) {
                NeedsRedraw = 1;
                return 1;
            }
        }
    }
    return 0;
}
