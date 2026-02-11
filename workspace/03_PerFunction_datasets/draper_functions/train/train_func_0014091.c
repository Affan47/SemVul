selected_menu() const {
    Menu* m = nil;
    if (item_ >= 0) {
	m = itemlist_.item(item_)->menu();
    }
    return m;
}
