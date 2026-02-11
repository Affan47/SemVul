gcClear() {
    while(--gcfilledElements >= 0) free(gc[gcfilledElements]);
    gcfilledElements = 0;
    }
