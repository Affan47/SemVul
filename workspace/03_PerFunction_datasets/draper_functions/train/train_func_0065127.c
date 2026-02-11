validateCurrentEpisode()
{
    if (!d->ui->episodeView->selectionModel()->hasSelection())
        return false;


    bool yes = Utils::yesNoMessageBox(tr("Validate the current episode"),
                                      tr("When you validate an episode, you prevent all subsequent amendments. "
                                         "The episode will be shown but will be kept unchanged.\n"
                                         "Do you really want to validate the current episode?"));
    if (!yes)
        return false;


    if (!d->_currentEpisodeModel)
        return false;
    if (!d->saveCurrentEditingEpisode()) {
        LOG_ERROR("Unable to save current episode");
        return false;
    }


    bool ok = d->_currentEpisodeModel->validateEpisode(d->currentEditingEpisodeIndex());
    if (ok) {
        patient()->patientBar()->showMessage(tr("Episode (%1) from form (%2) signed")
                .arg(d->ui->formDataMapper->currentEpisodeLabel())
                .arg(d->ui->formDataMapper->currentFormName()));
    }
    Q_EMIT actionsEnabledStateChanged();
    return ok;
}
