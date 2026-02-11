board_get_destroy_at_xy(gint x, gint y) {
        if(x >= _rules.width || y > _rules.height)
                return 0;
        return _board_destroys[y * _rules.width + x];
}
