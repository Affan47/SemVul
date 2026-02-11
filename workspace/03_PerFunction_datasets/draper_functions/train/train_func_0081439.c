onTextChanged(WindowEventArgs& e)
    {
        Editbox* editbox = getEditbox();


        if (editbox->getText() != getText())
        {


            editbox->setText(getText());
            ++e.handled;

            Window::onTextChanged(e);
        }
    }
