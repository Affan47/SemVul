locate (int array[], int wanted)
{
    int count;
    int found = array[wanted-1];

    for (count = 0; count < (num_inmates >> 1); count++) {
        if (found == wanted)
            return 1;
        found = array[found-1];
    }
    return 0;
}
