expandSourceRanges(UString::Range * & array, int& count, int& capacity)
{
  int newCapacity;
  if (capacity == 0) {
    newCapacity = 16;
  } else {
    newCapacity = capacity * 2;
  }

  UString::Range *newArray = new UString::Range[newCapacity];
  for (int i = 0; i < count; i++) {
    newArray[i] = array[i];
  }

  delete [] array;

  capacity = newCapacity;
  array = newArray;
}
