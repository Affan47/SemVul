SaveGUIPrefs()
{


	wxConfigBase *config = wxConfigBase::Get();

	if (config == NULL) {
		return false;
	}

	wxString section = wxT("/Razor_Preferences/");

	if (!IsIconized()) {

		int x1, y1, x2, y2;
		GetPosition(&x1, &y1);
		GetSize(&x2, &y2);


		config->Write(section+wxT("MAIN_X_POS"), (long) x1);
		config->Write(section+wxT("MAIN_Y_POS"), (long) y1);

		config->Write(section+wxT("MAIN_X_SIZE"), (long) x2);
		config->Write(section+wxT("MAIN_Y_SIZE"), (long) y2);

		config->Write(section+wxT("Maximized"), (long) (IsMaximized() ? 1 : 0));
	}


	config->Write(section+wxT("SRV_SPLITTER_POS"), (long) m_srv_split_pos);

	config->Flush(true);


	return true;
}
