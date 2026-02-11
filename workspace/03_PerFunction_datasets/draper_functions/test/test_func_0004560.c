createWidgetsAndObjects()
    {
        _cityLabel = new QLabel(q);
        _countryLabel = new QLabel(q);
        _stateLabel = new QLabel(q);
        _zipLabel = new QLabel(q);
        _streetLabel = new QLabel(q);

        _street = new QTextEdit(q);
        _street->setTabChangesFocus(true);
        _street->setMaximumHeight(50);
        _city = new Utils::QButtonLineEdit(q);
        _zip = new Utils::QButtonLineEdit(q);
        _stateCombo = new QComboBox(q);
        _stateCombo->setFocusPolicy(Qt::StrongFocus);
        _country = new Utils::CountryComboBox(q);
        _country->setFlagPath(settings()->path(Core::ISettings::SmallPixmapPath) + "/flags/");
        _country->initialize();
        _country->setFocusPolicy(Qt::StrongFocus);

        _zipCompleter = new ZipCodes::ZipCountryCompleters(q);
        _zipCompleter->setCityLineEdit(_city);
        _zipCompleter->setZipLineEdit(_zip);
        _zipCompleter->setCountryComboBox(_country);
        _zipCompleter->setStateProvinceComboBox(_stateCombo);
    }
