findSubImageAsyncFinished(const ActionTools::MatchingPointList &matchingPointList)
	{
		if(mFindSubImageAsyncFunction.isValid())
		{
			if(matchingPointList.isEmpty())
			{
				mFindSubImageAsyncFunction.call(thisObject(), QScriptValueList() << QScriptValue());

				return;
			}

			if(mFindSubImageSearchForOne)
			{
				const ActionTools::MatchingPoint &matchingPoint = matchingPointList.first();
				QScriptValue back = mFindSubImageAsyncFunction.engine()->newObject();

                back.setProperty("position", CodeClass::constructor(new Point(matchingPoint.position), mFindSubImageAsyncFunction.engine()));
                back.setProperty("confidence", matchingPoint.confidence);

				mFindSubImageAsyncFunction.call(thisObject(), QScriptValueList() << back);
			}
			else
			{
				ActionTools::MatchingPointList matchingPointListCopy(matchingPointList);
				qSort(matchingPointListCopy.begin(), matchingPointListCopy.end(), matchingPointGreaterThan);

				ActionTools::MatchingPointList::ConstIterator matchingPointIt = matchingPointListCopy.constBegin();
				QScriptValue back = mFindSubImageAsyncFunction.engine()->newArray(matchingPointListCopy.size());

				int index = 0;
				while(matchingPointIt != matchingPointListCopy.constEnd())
				{
					QScriptValue object = mFindSubImageAsyncFunction.engine()->newObject();

                    object.setProperty("position", CodeClass::constructor(new Point(matchingPointIt->position), mFindSubImageAsyncFunction.engine()));
                    object.setProperty("confidence", matchingPointIt->confidence);

					back.setProperty(index, object);

					++matchingPointIt;
					++index;
				}

				mFindSubImageAsyncFunction.call(thisObject(), QScriptValueList() << back);
			}
		}
	}
