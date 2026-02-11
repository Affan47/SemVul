main( int argc, char *argv[] )
{
	QApplication app( argc, argv );
	app.setQuitOnLastWindowClosed( true );


	QTranslator Translator( &app );

	Translator.load( SettingsManager::instance()->language() );
	app.installTranslator( &Translator );

	QMainWindow * MainForm = new MyMainWindow();

	if ( argc > 1 )
		{
			QString FileName ( argv[1] );
			QFileInfo FileInfo( FileName );
			cerr << "\n";
			cerr << APPNAME << " " << "doesn't accept commandline arguments.";
			cerr << "\n\n";
			cerr << APPNAME << " " << VERSION << ", (c) by " << AUTHOR << " " << YEARS << ".";
			cerr << "\n";
			cerr << APPNAME << " was released under terms and conditions of the GPL license, V2.";
			cerr << "\n";
			cerr << "For further information visit http://gebabbel.sourceforge.net";
			cerr << "\n\n";
		}
	MainForm->show();
	return app.exec();
}
