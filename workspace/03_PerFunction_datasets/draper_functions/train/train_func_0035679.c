handleButtonClick(PG_Button* button) {
	switch(button->GetID()) {

		case IDWINDOW_CLOSE:
			Hide();
			sigClose(this);
			break;


		case IDWINDOW_MINIMIZE:
			Hide();
			sigMinimize(this);
			break;
	}


	QuitModal();

	return true;
}
