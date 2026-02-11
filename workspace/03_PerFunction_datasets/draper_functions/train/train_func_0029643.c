_set_sp_rating_n(SpecialSortTabPage *self, gint n, gboolean state) {
    guint32 rating;
    guint32 inst = _get_sort_tab_widget_instance(self);

    if (SPECIAL_SORT_TAB_IS_PAGE(self) && (n <= RATING_MAX)) {
        rating = (guint32) prefs_get_int_index("sp_rating_state", inst);

        if (state)
            rating |= (1 << n);
        else
            rating &= ~(1 << n);

        prefs_set_int_index("sp_rating_state", inst, rating);
    }
}
