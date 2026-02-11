getResults(QList<InputData>* inputData, QList<CatItem>* results)
{
	if (inputData->count() > 0)
	{
		foreach(PluginInfo info, plugins)
		{
			if (info.loaded)
				info.obj->msg(MSG_GET_RESULTS, (void*) inputData, (void*) results);
		}
	}
}
