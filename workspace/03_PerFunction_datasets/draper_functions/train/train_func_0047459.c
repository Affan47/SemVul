reverse(float array[], le_int32 length)
{
    le_int32 front, back;

    for (front = 0, back = length - 1; front < back; front += 1, back -= 1) {
        float swap = array[front];

        array[front] = array[back];
        array[back]  = swap;
    }
}
