close(int filehandle){

    if (filehandle < 0 || filehandle >= MAX_OPEN) {
        return ERROR_FILE_HANDLE_OUT_OF_RANGE;
    }


    if (!(open_files[filehandle].bits & OPEN_TYPE_OPEN_BITMASK)){
        return ERROR_FILE_NOT_OPEN;
    }

    open_files[filehandle].file = null;
    open_files[filehandle].bits = 0;

    return ERROR_SUCCESS;
}
