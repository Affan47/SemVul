get_tuple(int fd, cisdata_t code, ds_ioctl_arg_t *arg){
    arg->tuple.DesiredTuple = code;
    arg->tuple.Attributes = TUPLE_RETURN_COMMON;
    arg->tuple.TupleOffset = 0;
    if((ioctl(fd, DS_GET_FIRST_TUPLE, arg) == 0) &&
        (ioctl(fd, DS_GET_TUPLE_DATA, arg) == 0) &&
        (ioctl(fd, DS_PARSE_TUPLE, arg) == 0)){
        return 0;
    }else{
        return -1;
    }
}
