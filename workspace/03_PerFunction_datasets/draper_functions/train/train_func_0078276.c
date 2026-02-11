draw(ecl::GC &gc, const ecl::Rect &r) {
    Button::draw(gc, r);
    string &fname = is_pressed() ? fname_sel : fname_unsel;

    if (Surface *s = enigma::GetImage(fname.c_str())) {
        int w=s->width();
        int h=s->height();
        int x = get_x() + (get_w()-w)/2;
        int y = get_y() + (get_h()-h)/2;
        blit(gc, x, y, s);
    }
}
