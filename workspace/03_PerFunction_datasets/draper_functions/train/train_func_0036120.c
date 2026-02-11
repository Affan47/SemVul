resize(int new_size) {

    bloom_vertex* _data = data;

    data = new bloom_vertex[new_size];

    for(int i=0;i<data_size;i++) {
        data[i] = _data[i];
    }

    data_size = new_size;

    if(_data != 0) delete[] _data;
}
