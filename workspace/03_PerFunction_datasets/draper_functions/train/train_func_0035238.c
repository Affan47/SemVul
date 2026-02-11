qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RichTextEditor *_t = static_cast<RichTextEditor *>(_o);
        switch (_id) {
        case 0: _t->textChanged(); break;
        case 1: _t->textBold(); break;
        case 2: _t->textUnderline(); break;
        case 3: _t->textItalic(); break;
        case 4: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->textColor(); break;
        case 6: _t->textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 10: _t->cursorPositionChanged(); break;
        case 11: { QString _r = _t->toHtml();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
