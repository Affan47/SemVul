copy(const Color &col_copy) {
    if (!col_copy.isAllocated()) {
        free();
        setRGB(col_copy.red(), col_copy.green(), col_copy.blue());
        setPixel(col_copy.pixel());
        return;
    }

    free();

    allocate(col_copy.red()*0xFF,
             col_copy.green()*0xFF,
             col_copy.blue()*0xFF,
             col_copy.m_screen);

}
