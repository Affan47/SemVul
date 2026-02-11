choose_pivot(int* array, int begin, int end){
  int tmp, middle = (begin+end)/2;

  if(array[begin] > array[middle]){

	 tmp = begin;
	 begin = middle;
	 middle = tmp;
  }

  if(array[begin] > array[end])
	 end = begin;

  if(array[middle] > array[end])
	 middle = end;

  return middle;
}
