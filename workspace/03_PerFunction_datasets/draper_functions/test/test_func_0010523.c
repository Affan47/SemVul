_k_updateUserText(const QString &txt)
    {
        if (!completionRunning && (txt != userText)) {
            userText = txt;
            q->setModified(true);
#ifndef KDE_NO_DEPRECATED
            emit q->userTextChanged(txt);
#endif
            emit q->textEdited(txt);
            emit q->textChanged(txt);
        }
    }
