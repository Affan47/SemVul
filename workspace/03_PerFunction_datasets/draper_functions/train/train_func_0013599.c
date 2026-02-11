property(QWidget *w) const
{


    QByteArray userproperty = getCustomProperty(w);
    if (userproperty.isEmpty()) {
        userproperty = getUserProperty(w);
    }
    if (userproperty.isEmpty()) {
        QComboBox *cb = qobject_cast<QComboBox *>(w);
        if (cb) {
            if (cb->isEditable()) {
                return QVariant(cb->currentText());
            } else {
                return QVariant(cb->currentIndex());
            }
        }
    }
    if (userproperty.isEmpty()) {
        kWarning(d->debugArea()) << w->metaObject()->className() << " widget not handled!";
        return QVariant();
    }

    return w->property(userproperty);
}
