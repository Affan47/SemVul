CheckNewButtonsState()
{
	switch (chatselector->GetPageCount()) {
			case 0:
				GetParent()->FindWindow(IDC_CSEND)->Enable(false);
				GetParent()->FindWindow(IDC_CCLOSE)->Enable(false);
				GetParent()->FindWindow(IDC_CMESSAGE)->Enable(false);
				break;
			case 1:
				GetParent()->FindWindow(IDC_CSEND)->Enable(true);
				GetParent()->FindWindow(IDC_CCLOSE)->Enable(true);
				GetParent()->FindWindow(IDC_CMESSAGE)->Enable(true);
				break;
			default:

				wxASSERT(GetParent()->FindWindow(IDC_CSEND)->IsEnabled());
				wxASSERT(GetParent()->FindWindow(IDC_CCLOSE)->IsEnabled());
				wxASSERT(GetParent()->FindWindow(IDC_CMESSAGE)->IsEnabled());
				break;
	}
}
