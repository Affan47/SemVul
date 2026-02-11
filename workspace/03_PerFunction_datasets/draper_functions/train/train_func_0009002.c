setNeedsAuthorization(bool needsAuth)
{
    d->_needsAuthorization = needsAuth;
    if (needsAuth && d->_about) {
        d->_authAction = new KAuth::Action(QString("org.kde.kcontrol." + d->_about->appName() + ".save"));
        d->_needsAuthorization = d->_authAction->isValid();
        d->_authAction->setHelperID("org.kde.kcontrol." + d->_about->appName());
        d->_authAction->setParentWidget(this);
        connect(d->_authAction->watcher(), SIGNAL(statusChanged(int)),
                this, SLOT(authStatusChanged(int)));
        authStatusChanged(d->_authAction->status());
    } else {
        d->_authAction = 0;
    }
}
