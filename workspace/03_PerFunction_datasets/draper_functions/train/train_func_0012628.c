_k_storageSetupDone(Solid::ErrorType error, QVariant errorData)
{
    QPersistentModelIndex index = setupInProgress.take(q->sender());

    if (!index.isValid()) {
        return;
    }

    if (!error) {
        emit q->setupDone(index, true);
    } else {
        if (errorData.isValid()) {
            emit q->errorMessage(i18n("An error occurred while accessing '%1', the system responded: %2",
                                      q->text(index),
                                      errorData.toString()));
        } else {
            emit q->errorMessage(i18n("An error occurred while accessing '%1'",
                                      q->text(index)));
        }
        emit q->setupDone(index, false);
    }

}
