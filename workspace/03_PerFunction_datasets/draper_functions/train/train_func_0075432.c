scrollLines()
{
    boost::uint16_t fontHeight = getFontHeight();
    const float fontLeading = 0;

    _linesindisplay = _bounds.height() / (fontHeight + fontLeading + PADDING_TWIPS);
    if (_linesindisplay > 0) {
        size_t manylines = _line_starts.size();
        size_t lastvisibleline = _scroll + _linesindisplay;
        size_t line = 0;


        if (manylines < _scroll) {
            _scroll = manylines - _linesindisplay;
            return;
        }


        while (line < manylines && _line_starts[line] <= m_cursor) {
            ++line;
        }

        if (manylines - _scroll <= _linesindisplay) {

            if (manylines < _linesindisplay) _scroll = 0;
            else {
                _scroll = manylines - _linesindisplay;
            }
        } else if (line < _scroll) {

            _scroll -= _scroll - line;
        } else if (manylines > _scroll + _linesindisplay) {

            if (line >= (_scroll+_linesindisplay)) {
                _scroll += line - (lastvisibleline);
            }
        }
    }
}
