FreeList() {
    if (Files) {
        for (int i = 0; i < FCount; i++)
            delete Files[i];
        free(Files);
    }
    Files = 0;
    FCount = 0;
}
