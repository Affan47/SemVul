text(const rectf &r) const
{
    std::auto_ptr<GooString> s;
    TextOutputDev td(0, gFalse, gFalse, gFalse);
    d->doc->doc->displayPage(&td, d->index + 1, 72, 72, 0, false, true, false);
    if (r.is_empty()) {
        const PDFRectangle *rect = d->page->getCropBox();
        s.reset(td.getText(rect->x1, rect->y1, rect->x2, rect->y2));
    } else {
        s.reset(td.getText(r.left(), r.top(), r.right(), r.bottom()));
    }
    return ustring::from_utf8(s->getCString());
}
