get_path_under_xy( int x, int y )
{
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn* column;
    int cell_x, cell_y;
    if( !get_path_at_pos( x, y, path, column, cell_x, cell_y ) ) return Gtk::TreeModel::Path();

    return path;
}
