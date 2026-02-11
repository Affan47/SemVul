startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes & atts)
{
	if( qName == "artefacts" && _state == StateInit ) {
		_state = StateDocument;
	} else if( qName == "artefact" && _state == StateDocument ) {
		_state = StateArtefact;
		_artefact = new GenericArtefactModel();
	} else if( qName == "name" && _state == StateArtefact ) {
		_state = StateName;
	} else if( qName == "position" && _state == StateArtefact ) {
		_state = StatePosition;
	} else if( qName == "action" && _state == StateArtefact ) {
		_state = StateAction;
	} else if( qName == "elementary" && _state == StateAction ) {
		ArtefactElementaryAction::ActionType action;
		ArtefactElementaryAction::ModifType modif;
		_state = StateActionElementary;
		if( atts.value( "type" ).toUpper() == "CHARAC" ) {
			action = ArtefactElementaryAction::AT_CHARAC;
		} else {
			action = ArtefactElementaryAction::AT_SKILL;
		}
		if( atts.value( "modif" ).toUpper() == "VALUE" ) {
			modif = ArtefactElementaryAction::MT_VALUE;
		} else {
			modif = ArtefactElementaryAction::MT_RATIO;
		}
		_action = new ArtefactElementaryAction( action, modif );
		_action->setParam( atts.value( "param" ).toInt() );
	} else {

		return false;
	}
	return true;
}
