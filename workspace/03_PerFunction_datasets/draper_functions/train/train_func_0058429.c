seek(long sample) {

    sample -= (sample % 64);


    f_seek_byte = sample*4 + f_start_byte;


    long pos = static_cast<long>(sample);
    updateCounters(pos);


    try {

        mCache->seek(f_seek_byte - f_pos_byte);
        f_pos_byte = f_seek_byte;
    }
    catch (int e) {

        threadSend(SEEK);
    }
}
