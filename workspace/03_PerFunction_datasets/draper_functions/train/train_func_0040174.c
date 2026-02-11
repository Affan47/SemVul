menutils_PrintQue(StreamInteractor* S) {
	printf("[ ");
	for(std::deque<std::string>::iterator it = S->mydeque->begin(); it != S->mydeque->end(); it++)
		printf("'%s' ",it->c_str());
	printf("]\n");
}
