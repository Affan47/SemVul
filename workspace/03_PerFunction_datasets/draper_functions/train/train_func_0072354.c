reject(void) {
    DBG(1, form("KCemu/Preferences",
                "Preferences::reject(): Start rejecting changes\n"));

    RejectVisitor visitor(this);
    visit_changed(visitor);

    DBG(1, form("KCemu/Preferences",
                "Preferences::reject(): End rejecting changes\n"));
}
