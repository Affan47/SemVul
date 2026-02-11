test_heapSort( ostream &os) {
	Heap heap;
	ifstream data( "test_heapSort.in");
	int node;
	while ( data >> node) {
		heap.push_back( node);
	}
	data.close();

	os << "Before heap sort" << std::endl;
	printHeap( os, heap);
	std::copy( heap.begin(), heap.end(), ostream_iterator<int>( std::cout, " "));
	os << std::endl;

	heapSort( heap);
	os << "After heap sort" << std::endl;
	printHeap( os, heap);
	std::copy( heap.begin(), heap.end(), ostream_iterator<int>( std::cout, " "));
	os << std::endl;
}
