StyleSetMessage(unsigned int iMessage, uptr_t wParam, sptr_t lParam) {
	vs.EnsureStyle(wParam);
	switch (iMessage) {
	case SCI_STYLESETFORE:
		vs.styles[wParam].fore.desired = ColourDesired(lParam);
		break;
	case SCI_STYLESETBACK:
		vs.styles[wParam].back.desired = ColourDesired(lParam);
		break;
	case SCI_STYLESETBOLD:
		vs.styles[wParam].bold = lParam != 0;
		break;
	case SCI_STYLESETITALIC:
		vs.styles[wParam].italic = lParam != 0;
		break;
	case SCI_STYLESETEOLFILLED:
		vs.styles[wParam].eolFilled = lParam != 0;
		break;
	case SCI_STYLESETSIZE:
		vs.styles[wParam].size = lParam;
		break;
	case SCI_STYLESETFONT:
		if (lParam != 0) {
			vs.SetStyleFontName(wParam, CharPtrFromSPtr(lParam));
		}
		break;
	case SCI_STYLESETUNDERLINE:
		vs.styles[wParam].underline = lParam != 0;
		break;
	case SCI_STYLESETCASE:
		vs.styles[wParam].caseForce = static_cast<Style::ecaseForced>(lParam);
		break;
	case SCI_STYLESETCHARACTERSET:
		vs.styles[wParam].characterSet = lParam;
		break;
	case SCI_STYLESETVISIBLE:
		vs.styles[wParam].visible = lParam != 0;
		break;
	case SCI_STYLESETCHANGEABLE:
		vs.styles[wParam].changeable = lParam != 0;
		break;
	case SCI_STYLESETHOTSPOT:
		vs.styles[wParam].hotspot = lParam != 0;
		break;
	}
	InvalidateStyleRedraw();
}
