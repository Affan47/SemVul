endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
		{
			--depth;
			if(depth == 0) {
				Parser::Event *e = new Parser::Event;
				e->setDocumentClose(namespaceURI, localName, qName);
				e->setActualString(in->lastString());
				in->resetLastData();
				eventList.append(e);
				in->pause(true);
			}
			else {

				if(depth == 1) {
					Parser::Event *e = new Parser::Event;
					e->setElement(elem);
					e->setActualString(in->lastString());
					in->resetLastData();
					eventList.append(e);
					in->pause(true);

					elem = QDomElement();
					current = QDomElement();
				}
				else
					current = current.parentNode().toElement();
			}

			if(in->lastRead() == '/')
				checkNeedMore();

			return true;
		}
