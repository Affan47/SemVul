showHint()
{

    QString caption = i18n ("Hint");

    if (levelHint.length() > 0) {
	freeze (ProgramPause, true);

	switch (KGrMessage::warning (view, caption, levelHint,
			    i18n ("&OK"), i18n ("&Show A Solution"))) {
	case 0:
	    freeze (ProgramPause, false);
	    break;
	case 1:
	    freeze (ProgramPause, false);

            runReplay (SOLVE, gameIndex, level);
	    break;
	}
    }
    else
        myMessage (view, caption,
                        i18n ("Sorry, there is no hint for this level."));
}
