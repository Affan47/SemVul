processStep()
{
	Parser::Event pe;
	notify = 0;
	transferItemList.clear();

	if(state != Closing && (state == RecvOpen || stepAdvancesParser())) {

		pe = xml.readNext();
		if(!pe.isNull()) {

			switch(pe.type()) {
				case Parser::Event::DocumentOpen: {
					transferItemList += TransferItem(pe.actualString(), false);


					break;
				}
				case Parser::Event::DocumentClose: {
					transferItemList += TransferItem(pe.actualString(), false);


					if(incoming) {
						sendTagClose();
						event = ESend;
						peerClosed = true;
						state = Closing;
					}
					else {
						event = EPeerClosed;
					}
					return true;
				}
				case Parser::Event::Element: {
					QDomElement e = elemDoc.importNode(pe.element(),true).toElement();
					transferItemList += TransferItem(e, false);


					break;
				}
				case Parser::Event::Error: {
					if(incoming) {


						if(state == RecvOpen) {
							sendTagOpen();
							state = Open;
						}
						return handleError();
					}
					else {
						event = EError;
						errorCode = ErrParse;
						return true;
					}
				}
			}
		}
		else {
			if(state == RecvOpen || stepRequiresElement()) {
				need = NNotify;
				notify |= NRecv;
				return false;
			}
		}
	}

	return baseStep(pe);
}
