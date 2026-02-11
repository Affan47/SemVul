doNextStep(){
	TraceFileLine line;
	getNextLine(&line);
	if (ONE_SECOND_PASSED) {
		start = clock();
		seconds++;

	}
	if(myLastStepWorked){

		switch(line.type) {
			case 'w':
			    (*this.*operRefChange)(line);
				break;
			case 'a':
			    (*this.*operAllocate)(line);


				getNextLine(NULL);
				break;
			case '+':
				addToRoot(line);
				break;
			case '-':
				deleteRoot(line);
				break;
			case 'c':

				referenceOperationClassField(line);
				break;
			case 'r':

				readOperation(line);
				break;
			case 's':
				storeOperation(line);
				break;

			default:

			break;
		}

	}

	if (forceAGCAfterEveryStep)
		myMemManager->forceGC();


	return 0;
}
