startExecution()
	{
		bool ok = true;

		QString title = evaluateString(ok, "title");
		Action action = evaluateListElement<Action>(ok, actions, "action");
		bool useBorders = evaluateBoolean(ok, "useBorders");

		if(!ok)
			return;

		QPoint movePosition;
		int resizeWidth = 0;
		int resizeHeight = 0;

		if(action == Move)
		{
			movePosition = evaluatePoint(ok, "movePosition");
			if(!ok)
				return;
		}
		else if(action == Resize)
		{
			resizeWidth = evaluateInteger(ok, "resizeWidth");
			resizeHeight = evaluateInteger(ok, "resizeHeight");
			if(!ok)
				return;
		}

		ActionTools::WindowHandle foundWindow = ActionTools::WindowHandle::findWindow(QRegExp(title, Qt::CaseSensitive, QRegExp::WildcardUnix));

		if(!foundWindow.isValid())
		{
			setCurrentParameter("title");
			emit executionException(CannotFindWindowException, tr("Cannot find any window matching \"%1\"").arg(title));
			return;
		}

		bool result = true;

		switch(action)
		{
		case Close:
			result = foundWindow.close();
			break;
		case KillProcess:
			result = foundWindow.killCreator();
			break;
		case SetForeground:
			result = foundWindow.setForeground();
			break;
		case Minimize:
			result = foundWindow.minimize();
			break;
		case Maximize:
			result = foundWindow.maximize();
			break;
		case Move:
			result = foundWindow.move(movePosition);
			break;
		case Resize:
			result = foundWindow.resize(QSize(resizeWidth, resizeHeight), useBorders);
			break;
		}

		if(!result)
		{
			setCurrentParameter("action");
			emit executionException(ActionFailedException, tr("\"%1\" failed").arg(actions.second[action]));
			return;
		}

		emit executionEnded();
	}
