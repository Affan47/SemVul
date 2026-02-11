slotTimeout()
    {
        kWarning() << "Plasmoid access job timed out";
        q->setError(-1);
        q->setErrorText(i18n("Timeout"));
        q->emitResult();
    }
