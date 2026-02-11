setModified(bool modified)
{
    d->_modified = modified;
    for(int i=0; i < d->_timings.count(); ++i) {
        d->_timings[i].setModified(modified);
    }
    for(int i=0; i < d->_relations.count(); ++i) {
        d->_relations[i].setModified(modified);
    }
    for(int i=0; i < d->_scripts.count(); ++i) {
        d->_scripts[i].setModified(modified);
    }
    for(int i=0; i < d->_validations.count(); ++i) {
        d->_validations[i].setModified(modified);
    }
}
