startNotify()


{
    if (!flags.notifyEnabled || flags.isEngineModifying)
	return;

    SoDB::startNotify();


    SoNotList	list;


    notify(&list);

    SoDB::endNotify();
}
