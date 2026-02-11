MakeBitmap(void* bits, int width, int height) {
    Bitmap* b = new Bitmap(bits, width, height);
    b->Reference();
    return b;
}
