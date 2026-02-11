operator[](int index)
{
    if ((index>=0)&&(index<nbBlobs)) return blobInfo[index];
    else camError("CamBlobs","Index out of range");
    return blobInfo[0];
}
