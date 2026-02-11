OnRescanUsb(wxCommandEvent &event)
{
	if( m_current_mode == m_main_menu_mode.get() ) {
		std::auto_ptr<UsbScanSplash> splash( new UsbScanSplash );
		wxGetApp().Probe();
		CreateDeviceCombo(wxGetApp().GetGlobalConfig().GetLastDevice());
		m_rescan_pending = false;
	}
	else {


		m_rescan_pending = true;
	}
}
