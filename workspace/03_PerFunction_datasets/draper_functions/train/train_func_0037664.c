gphoto_display_photo_window(iTunesDB *itdb) {
    if (!photo_editor || !photo_editor->window) {
        create_photo_editor();
    }
    else {
        gtkpod_display_widget(photo_editor->window);
    }
    gphoto_set_itdb(itdb);
}
