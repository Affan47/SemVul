SetIcon(const std::string& filename) {
	if(my_freeicon) {
		PG_Application::UnloadSurface(my_srfIcon);
	}

	my_srfIcon = PG_Application::LoadSurface(filename);
	my_freeicon = true;
	Update();

	return my_srfIcon;
}
