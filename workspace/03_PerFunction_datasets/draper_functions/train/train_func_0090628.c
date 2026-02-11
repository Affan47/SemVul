main(int argc, char *argv[])
{
	INIT_I18N(PACKAGE);

	cout.sync_with_stdio(true);


	try {

		bool data_dump = false,
			get_meid = false,
			get_usb_serial = false,
			show_both = false;
		string busname;
		string devname;


		for(;;) {
			int cmd = getopt(argc, argv, "B:hN:vmsc");
			if( cmd == -1 )
				break;

			switch( cmd )
			{
			case 'B':
				busname = optarg;
				break;

			case 'N':
				devname = optarg;
				break;

			case 'c':
				show_both = true;
				break;

			case 'm':
				get_meid = true;
				break;

			case 's':
				get_usb_serial = true;
				break;

			case 'v':
				data_dump = true;
				break;

			case 'h':
			default:
				Usage();
				return 0;
			}
		}

		Barry::Init(data_dump, &std::cerr);
		Barry::Probe probe(busname.c_str(), devname.c_str());


		for( int i = 0; i < probe.GetCount(); i++ ) {
			const ProbeResult &pr = probe.Get(i);
			cout 	<< pr.m_pin.Str() << ", "
				<< pr.m_description;

			if( get_meid ) try {
				Barry::Controller con(pr);
				Barry::Mode::Desktop desktop(con);
				desktop.Open();


				string meid = FetchMEID(desktop);
				cout << ", " << meid;

				if( show_both ) {
					if( HandheldAgent::IsESNHex(meid) ) {
						cout << " (" << HandheldAgent::ESNHex2Dec(meid) << ")";
					}
					else if( HandheldAgent::IsESNDec(meid) ) {
						cout << " (" << HandheldAgent::ESNDec2Hex(meid) << ")";
					}
				}
			}
			catch( Barry::BadPassword & ) {

			}
			catch( Barry::Error &e ) {


				cerr << _("Error on PIN: ") << pr.m_pin.Str() << ": " << e.what() << endl;
			}

			if( get_usb_serial ) {
				Usb::Device dev(pr.m_dev);
				cout << ", " << dev.GetSimpleSerialNumber();
			}


			cout << endl;
		}

		return probe.GetFailCount();

	}
	catch( std::exception &e ) {
		cerr << _("exception caught: ") << e.what() << endl;
		return 1;
	}
}
