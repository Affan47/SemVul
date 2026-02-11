end_button_style(
    Glyph* g, TelltaleState* t, Action* a
) {
    Button* b = new Button(g, style(), t, a);
    kit_->end_style();
    return b;
}
