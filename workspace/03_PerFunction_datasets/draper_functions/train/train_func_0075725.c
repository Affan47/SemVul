onValueChanged(WindowEventArgs& e)
    {
        Editbox* editbox = getEditbox();


        bool wasMuted = editbox->isMuted();
        editbox->setMutedState(true);


        if (!(d_currentValue == 0 &&
              (editbox->getText().empty() || editbox->getText() == "-")))
        {
            editbox->setText(getTextFromValue());
        }

        editbox->setMutedState(wasMuted);

        fireEvent(EventValueChanged, e, EventNamespace);
    }
