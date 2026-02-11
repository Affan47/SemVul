getMatrix(SoGetMatrixAction *action)


{

    if (path.getValue() != NULL &&
	matchesPath(path.getValue(), action->getCurPath()))
	SoGroup::getMatrix(action);
}
