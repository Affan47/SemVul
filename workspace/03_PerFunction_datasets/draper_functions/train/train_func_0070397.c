clear() {
    delete[] fElements;

    fElements = 0;
    fCapacity = 0;
    fCount = 0;
}
