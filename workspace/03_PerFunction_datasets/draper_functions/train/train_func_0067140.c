flush() {
    PrinterRep* p = rep_;
    ostream& out = *p->out_;
    if (p->text_chars_ > 0) {
        out << ") ";
        if (p->text_spaces_ > 0) {
            out << p->text_spaces_ << " " << (double)p->text_curx_ << " ws\n";
        } else {
            out << p->text_chars_ << " " << (double)p->text_curx_ << " as\n";
        }
        p->text_chars_ = 0;
        p->text_spaces_ = 0;
    }
}
