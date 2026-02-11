itemType() const
{
    if (hasFormat("item/type"))
        return (UnicornEnums::ItemType) QString::fromUtf8(data("item/type")).toInt();

    if (hasFormat("item/track"))
        return UnicornEnums::ItemTrack;
    if (hasFormat("item/album"))
        return UnicornEnums::ItemAlbum;
    if (hasFormat("item/artist"))
        return UnicornEnums::ItemArtist;

    return UnicornEnums::ItemUnknown;
}
