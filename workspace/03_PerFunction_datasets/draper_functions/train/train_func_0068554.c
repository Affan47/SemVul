retranslate()
{
    if (!d->searchByNameAct)
        return;
    d->searchByNameAct->setText(tr("Search user by name"));
    d->searchByFirstnameAct->setText(tr("Search user by firstname"));
    d->searchByNameAndFirstnameAct->setText(tr("Search user by name and firstname"));
    d->searchByCityAct->setText(tr("Search user by city"));

    d->searchByNameAct->setToolTip(d->searchByNameAct->text());
    d->searchByFirstnameAct->setToolTip(d->searchByFirstnameAct->text());
    d->searchByNameAndFirstnameAct->setToolTip(d->searchByNameAndFirstnameAct->text());
    d->searchByCityAct->setToolTip(d->searchByCityAct->text());
    d->m_SearchToolButton->setToolTip(d->m_SearchToolButton->text());

    d->aCreateUser->setText(QCoreApplication::translate(Constants::TR_CONTEXT_USERS, Constants::CREATE_USER));
    d->aModifyUser->setText(QCoreApplication::translate(Constants::TR_CONTEXT_USERS, Constants::MODIFY_USER));
    d->aSave->setText(QCoreApplication::translate(Constants::TR_CONTEXT_USERS, Constants::SAVE_USER));
    d->aRevert->setText(tr("Clear modifications"));
    d->aDeleteUser->setText(QCoreApplication::translate(Constants::TR_CONTEXT_USERS, Constants::DELETE_USER));
    d->aQuit->setText(tr("Quit User Manager"));
    d->aToggleSearchView->setText(tr("Search user"));
    d->aCreateUser->setToolTip(d->aCreateUser->text());
    d->aModifyUser->setToolTip(d->aModifyUser->text());
    d->aSave->setToolTip(d->aSave->text());
    d->aRevert->setToolTip(d->aRevert->text());
    d->aDeleteUser->setToolTip(d->aDeleteUser->text());
    d->aQuit->setToolTip(d->aQuit->text());
    d->aToggleSearchView->setToolTip(d->aToggleSearchView->text());
}
