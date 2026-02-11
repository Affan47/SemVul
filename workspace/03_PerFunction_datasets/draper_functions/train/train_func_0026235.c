drawLayerObject(int layer, GLEMemoryCell* object) {
	GLEClassInstance* classObj = getGLEClassInstance(object, g_graphBlockData->getGraphBlockBase()->getClassDefinitions()->getFill());
	if (classObj != 0) {
		int index = classObj->getArray()->getInt(0);
		if (shouldDraw(index) && fd[index]->layer == layer) {
			g_gsave();
			drawFill(index);
			g_grestore();
		}
	}
}
