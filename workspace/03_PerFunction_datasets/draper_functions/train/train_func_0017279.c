Reset()
{
    errMess[0] = '\0';
    mode = External;
    lodInfo.resize(0);
    valid = true;
    currentRow = -1;
    currentCol = -1;

}
