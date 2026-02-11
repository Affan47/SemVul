commitChangesGLE(GLEScript* script) {
	m_Script = script;
	if (script == NULL) {
		cerr << "GLEInterface::commitChangesGLE(): script == NULL" << endl;
		return;
	}
	try {
		setCommitMode(true);
		setMakeDrawObjects(true);
		GLEDevice* old_device = g_set_dummy_device();
		TeXInterface* interface = TeXInterface::getInstance();
		GLEFileLocation output;
		output.createIllegal();
		interface->initialize(script->getLocation(), &output);
		interface->reset();
		script->resetObjectIterator();
		DrawIt(m_Script, &output, &g_CmdLine);
		for (int i = 0; i < script->getNumberNewObjects(); i++) {
			string code;
			GLEDrawObject* obj = script->getNewObject(i);
			if (!obj->hasFlag(GDO_FLAG_DELETED)) {
				obj->createGLECode(code);

				GLEPoint amove;
				bool needs_amove = false;
				if (obj->needsAMove(amove)) {

					GLEPoint crpt;
					g_get_xy(&crpt);
					if (!crpt.approx(amove)) {
						needs_amove = true;
						script->getSource()->addLine("");
					}
				}

				handleNewProperties(script->getSource(), obj->getProperties());

				if (needs_amove) {
					ostringstream amovec;
					amovec << "amove " << amove.getX() << " " << amove.getY();
					script->getSource()->addLine(amovec.str());
				}
				script->getSource()->addLine(code);

				obj->updateBoundingBox();
				script->addObject(obj);
			}
		}
		script->getSource()->performUpdates();
		script->clearNewObjects();
		script->removeDeletedObjects();
		interface->tryCreateHash();
		g_restore_device(old_device);
		setMakeDrawObjects(false);
		setCommitMode(false);
	} catch (ParserError err) {
		string err_str;
		err.toString(err_str);
		str_uppercase_initial_capital(err_str);
		g_message(err_str);
		m_Output->setExitCode(1);
	}
}
