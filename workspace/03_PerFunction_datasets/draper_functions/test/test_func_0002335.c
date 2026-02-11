getAccessKey(int index)
{
    if (index == 10) {
        abuf[0] = '*';
        abuf[1] = '\0';
    } else if (index == 11) {
        abuf[0] = '0';
        abuf[1] = '\0';
    } else if (index == 12) {
        abuf[0] = '#';
        abuf[1] = '\0';
    } else {
        sprintf(abuf,"%d",index);
    }
    return abuf;
}
