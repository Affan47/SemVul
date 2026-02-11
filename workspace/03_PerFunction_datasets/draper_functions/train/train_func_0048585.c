binary_heap_insert(BinaryHeap *heap, BinaryHeapValue value)
{
	BinaryHeapValue *new_values;
	unsigned int index;
	unsigned int new_size;
	unsigned int parent;


	if (heap->num_values >= heap->alloced_size) {


		new_size = heap->alloced_size * 2;
		new_values = realloc(heap->values, sizeof(BinaryHeapValue) * new_size);

		if (new_values == NULL) {
			return 0;
		}

		heap->alloced_size = new_size;
		heap->values = new_values;
	}


	index = heap->num_values;
	++heap->num_values;


	while (index > 0) {


		parent = (index - 1) / 2;


		if (binary_heap_cmp(heap, heap->values[parent], value) < 0) {


			break;

		} else {


			heap->values[index] = heap->values[parent];


			index = parent;
		}
	}


	heap->values[index] = value;

	return 1;
}
