setCompletionModel(QAbstractItemModel *completionModel)
	{
		mCompleter->setModel(completionModel);

		if(!mCompletionModelSet)
		{
			mCompletionModelSet = true;

			QStandardItemModel *standardItemCompletionModel = qobject_cast<QStandardItemModel *>(completionModel);
			if(!standardItemCompletionModel)
				return;

			for(int actionIndex = 0; actionIndex < standardItemCompletionModel->rowCount(); ++actionIndex)
			{
				QStandardItem *item = standardItemCompletionModel->item(actionIndex, 0);
				if(!item)
					continue;

				mHighlighter->addCodeObject(item->text());
			}
		}
	}
