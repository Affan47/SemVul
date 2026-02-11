init_fs(int device){
    int i;

    for (i = 0; i < MAX_DEVICE; i++){
        device_array[i].bits = device_array[i].bits & (~DEVICE_MOUNTED_BITMASK);
    }


    for (i = 0; i < MAX_OPEN; i++){
        open_files[i].bits = open_files[i].bits | (~OPEN_TYPE_OPEN_BITMASK);
        open_files[i].file = null;
    }


    for (i = 0; i < NUM_BUFFERS; i++) {
        buf_flush(i);
    }

    device_array[device].bits = device_array[device].bits | DEVICE_INIT_BITMASK;
    return ERROR_SUCCESS;
}
