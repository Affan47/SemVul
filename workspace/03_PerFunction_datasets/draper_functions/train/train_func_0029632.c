setItemsCheckable(bool state)
{
    StringListModel *m = qobject_cast<StringListModel*>(this->model());
    if (m)
        m->setCheckable(state);
}
