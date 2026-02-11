unlock(const std::string &owner_password, const std::string &user_password)
{
    if (d->is_locked) {
        document_private *newdoc = 0;
        if (d->doc_data.size() > 0) {
            newdoc = new document_private(&d->doc_data,
                                          owner_password, user_password);
        } else {
            newdoc = new document_private(new GooString(d->doc->getFileName()),
                                          owner_password, user_password);
        }
        if (!newdoc->doc->isOk()) {
            d->doc_data.swap(newdoc->doc_data);
            delete newdoc;
        } else {
            delete d;
            d = newdoc;
            d->is_locked = false;
        }
    }
    return d->is_locked;
}
