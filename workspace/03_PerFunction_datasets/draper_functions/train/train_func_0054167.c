init_chset(){
    Char = chset_t("\x9\xA\xD\x20-\x7f\x80\x81-\xFF");
    Letter = chset_t("\x41-\x5A\x61-\x7A\xC0-\xD6\xD8-\xF6\xF8-\xFF");
    Digit = chset_t("0-9");
    Extender = chset_t('\xB7');
    Sch = chset_t("\x20\x9\xD\xA");
    NameChar = Letter | Digit | chset_p("._:-") | Extender ;
}

}
