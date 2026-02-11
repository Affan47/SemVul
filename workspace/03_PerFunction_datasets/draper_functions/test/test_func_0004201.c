save(void) {
    DBG(1, form("KCemu/Preferences",
                "Preferences::save(): Start save profiles:\n"));

    mkdirs(_usr_dir);
    mkdirs(_add_dir);

    SaveVisitor visitor(this);
    visit_changed(visitor);

    DBG(1, form("KCemu/Preferences",
                "Preferences::save(): End save profiles.\n"));
}
