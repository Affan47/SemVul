ReadCurrentPos(jack_position_t* pos)
{
    UInt16 next_index = GetCurrentIndex();
    UInt16 cur_index;
    do {
        cur_index = next_index;
        memcpy(pos, ReadCurrentState(), sizeof(jack_position_t));
        next_index = GetCurrentIndex();
    } while (cur_index != next_index);
}
