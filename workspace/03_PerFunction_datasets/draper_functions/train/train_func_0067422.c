savePresets		(const char *filename)
{
	ofstream file( filename, ios::out );

	file << "amSynth" << endl;
	for (int i = 0; i < kNumPresets; i++) {
		if (presets[i].getName()!="unused"){
#ifdef _DEBUG
			cout << "<PresetController::savePresets():- preset: name= "
			<< presets[i].getName() << endl;
#endif
			file << "<preset> " << "<name> " << presets[i].getName() << endl;
			for (unsigned n = 0; n < presets[i].ParameterCount(); n++)
			{
#ifdef _DEBUG
				cout << "PresetController::savePresets() :- parameter name="
				<< presets[i].getParameter(n).getName() << " value= "
				<< presets[i].getParameter(n).getValue() << endl;
#endif
				file << "<parameter> "
				<< presets[i].getParameter(n).getName()
				<< " " << presets[i].getParameter(n).getValue() << endl;
			}
		}
	}
	file << "EOF" << endl;
	file.close();
#ifdef _DEBUG
	cout << "<PresetController::savePresets() success" << endl;
#endif
	return 0;
}
