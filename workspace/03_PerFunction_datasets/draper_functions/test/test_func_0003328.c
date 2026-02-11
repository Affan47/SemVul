initialize()
{

    if (d->_model)
        return true;


    if (!d->_base->initialize())
        return false;


    d->_model = new UserModel(this);
    d->_model->initialize();
    d->_coreUserModelWrapper = new CoreUserModelWrapper(this);
    d->_coreUserModelWrapper->initialize(d->_model);
    Core::ICore::instance()->setUser(d->_coreUserModelWrapper);
    connect(settings(), SIGNAL(userSettingsSynchronized()), d->_model, SLOT(updateUserPreferences()), Qt::UniqueConnection);

    return true;
}
