goBackOne(collIterate *data) {
# if 0


    if(data->pos) {
        data->pos--;
    }
    if(data->iterator) {
        data->iterator->previous(data->iterator);
    }
#endif
    if(data->iterator && (data->flags & UCOL_USE_ITERATOR)) {
        data->iterator->previous(data->iterator);
    }
    if(data->pos) {
        data->pos --;
    }
}
