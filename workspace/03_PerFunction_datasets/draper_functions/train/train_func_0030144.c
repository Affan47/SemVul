setPhoto(const QPixmap &pix)
{
    setDynamicDataValue(USER_DATA_PHOTO, Utils::pixmapToBase64(pix));
}
