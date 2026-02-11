updateLocationWhatsThis()
{
    QString whatsThisText;
    if (operationMode == KFileWidget::Saving)
    {
        whatsThisText = "<qt>" + i18n("This is the name to save the file as.") +
                             i18n (autocompletionWhatsThisText);
    }
    else if (ops->mode() & KFile::Files)
    {
        whatsThisText = "<qt>" + i18n("This is the list of files to open. More than "
                             "one file can be specified by listing several "
                             "files, separated by spaces.") +
                              i18n (autocompletionWhatsThisText);
    }
    else
    {
        whatsThisText = "<qt>" + i18n("This is the name of the file to open.") +
                             i18n (autocompletionWhatsThisText);
    }

    locationLabel->setWhatsThis(whatsThisText);
    locationEdit->setWhatsThis(whatsThisText);
}
