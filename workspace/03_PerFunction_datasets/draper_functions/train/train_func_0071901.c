nextWordPosition() const
{
    if (isEmpty())
        return Position();

    Position pos = *this;
    for (PositionIterator it(*this); !it.atEnd(); it.next()) {
        if (it.current().node()->nodeType() == Node::TEXT_NODE || it.current().node()->nodeType() == Node::CDATA_SECTION_NODE) {

            DOMString t = it.current().node()->nodeValue();
            QChar *chars = t.unicode();
            uint len = t.length();
            int start, end;
            khtml::findWordBoundary(chars, len, it.current().offset(), &start, &end);
            pos = Position(it.current().node(), end);
        }
        else {
            pos = Position(it.current().node(), it.current().node()->caretMaxOffset());
        }
        if (pos != *this)
            return pos;
        it.setPosition(pos);
    }

    return *this;
}
