ReGenerateCaptcha(uint32 nLetterCount)
{
	static wxString schCaptchaContent = wxT("ABCDEFGHJKLMNPQRSTUVWXYZ123456789");
	m_strCaptchaText.Clear();

	wxBitmap pimgResult(LETTERSIZE + (nLetterCount-1)*CROWDEDSIZE, 36);
	wxMemoryDC dc(pimgResult);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	double lastrotate = 15.0;

	for (uint32 i = 0; i < nLetterCount; i++) {
		wxString strLetter(schCaptchaContent[GetRandomUint16() % schCaptchaContent.length()]);
		m_strCaptchaText += strLetter;

		uint16 nRandomSize = 30 - GetRandomUint16() % 12;
		wxFont font(nRandomSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		dc.SetFont(font);
		uint16 nRandomOffset = 3 + GetRandomUint16() % 8;
		uint16 maxRotate = 50 - nRandomSize;
		double fRotate = (double)(maxRotate - (GetRandomUint16() % (maxRotate*2)));


		if (fRotate - lastrotate > 20) {
			fRotate = lastrotate + 20;
		} else if (fRotate - lastrotate < -20) {
			fRotate = lastrotate - 20;
		}
		dc.DrawRotatedText(strLetter, nRandomOffset + i * CROWDEDSIZE, 0, fRotate);
	}
	m_pimgCaptcha = pimgResult.ConvertToImage();

	m_pimgCaptcha.SetOption(wxIMAGE_OPTION_BMP_FORMAT, wxBMP_1BPP);

}
