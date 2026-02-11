notify(SoNotList *list)


{

    if (flags.dirty || ! flags.notifyEnabled || flags.isEngineModifying)
	return;


    if (!flags.connectionEnabled && (list->getLastRec() != NULL)) {

	SoNotRec::Type t = list->getLastRec()->getType();
	if (t == SoNotRec::ENGINE || t == SoNotRec::FIELD)
	    return;
    }


    flags.dirty = TRUE;


    SoFieldContainer	*cont = getContainer();

    if (cont != NULL) {


	SoNotRec	rec(cont);
	list->append(&rec, this);
	list->setLastType(SoNotRec::CONTAINER);


	if (! flags.hasAuditors)
	    cont->notify(list);


	else {
	    SoNotList listCopy(*list);
	    cont->notify(list);
	    auditorInfo->auditors.notify(&listCopy);
	}
    }
}
