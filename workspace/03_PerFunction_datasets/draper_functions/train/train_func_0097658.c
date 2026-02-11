goMessage(size_t messageNum,
			 string mimeid,
			 void (myMessage::*completedFuncArg)())
{
	openMessage(messageNum, mimeid, false, completedFuncArg);
}
