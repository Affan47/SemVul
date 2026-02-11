printLL() {
	List *temp = head;
	std::cout << "==Linked List: " << temp <<  "==\n";

	for(unsigned int i = 0; i < size; i++) {
		std::cout << temp << "\n";
		std::cout << "\tNext: " << temp->getNext() << "\n";
		std::cout << "\tPrev: " << temp->getPrev() << "\n";
		std::cout << "\tData: " << temp->getData() << "\n";
		temp = temp->getNext();
	}
}
