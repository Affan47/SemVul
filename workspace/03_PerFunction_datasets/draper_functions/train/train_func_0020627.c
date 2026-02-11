toggleSearchView(bool checked)
{
    if (checked) {
        d->ui->splitter->setSizes(QList<int>() << 1 << 3);
    } else {
        d->ui->splitter->setSizes(QList<int>() << 0 << 1);
    }
}
