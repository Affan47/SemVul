get_filesys_controller (const TCHAR *hdc)
{
	int hdcv = HD_CONTROLLER_UAE;
	if(_tcslen (hdc) >= 4 && !_tcsncmp (hdc, _T("ide"), 3)) {
		hdcv = hdc[3] - '0' + HD_CONTROLLER_IDE0;
		if (hdcv < HD_CONTROLLER_IDE0 || hdcv > HD_CONTROLLER_IDE3)
			hdcv = 0;
	}
	if(_tcslen (hdc) >= 5 && !_tcsncmp (hdc, _T("scsi"), 4)) {
		hdcv = hdc[4] - '0' + HD_CONTROLLER_SCSI0;
		if (hdcv < HD_CONTROLLER_SCSI0 || hdcv > HD_CONTROLLER_SCSI6)
			hdcv = 0;
	}
	if (_tcslen (hdc) >= 6 && !_tcsncmp (hdc, _T("scsram"), 6))
		hdcv = HD_CONTROLLER_PCMCIA_SRAM;
	if (_tcslen (hdc) >= 5 && !_tcsncmp (hdc, _T("scide"), 6))
		hdcv = HD_CONTROLLER_PCMCIA_IDE;
	return hdcv;
}
