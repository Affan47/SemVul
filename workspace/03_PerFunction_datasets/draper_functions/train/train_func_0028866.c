Remove (int index) {
    if (0 <= index && index < _count) {
        --_count;
        void** spot = &_buf[index];
        Memory::copy(spot+1, spot, (_count - index)*sizeof(void*));
    }
}
