PerformUndoStep() {

    const char *changesState = uh.GetChangesStep();
    lv.SetChanges(changesState);

	const Action &actionStep = uh.GetUndoStep();
	if (actionStep.at == insertAction) {

        BasicDeleteChars(actionStep.position, actionStep.lenData, true);

	} else if (actionStep.at == removeAction) {

        BasicInsertString(actionStep.position, actionStep.data, actionStep.lenData, true);

	}
	uh.CompletedUndoStep();
}
