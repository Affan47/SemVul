checkSelectAll() {
    if(lineEdit() && !lineEdit()->hasSelectedText() && isEnabled()) {
        lineEdit()->selectAll();
    }
}
