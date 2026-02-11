slotFindNext()
{
    if (!d->find)
        return;
    if(document()->isEmpty())
    {
        d->find->disconnect(this);
        d->find->deleteLater();
        d->find = 0;
        return;
    }

    KFind::Result res = KFind::NoMatch;
    if (d->find->needData())
        d->find->setData(toPlainText(), d->findIndex);
    res = d->find->find();

    if (res == KFind::NoMatch) {
        d->find->displayFinalDialog();
        d->find->disconnect(this);
        d->find->deleteLater();
        d->find = 0;

    } else {

    }
}
